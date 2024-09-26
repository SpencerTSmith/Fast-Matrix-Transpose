#include <stdio.h>
#include <string.h>
#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

void basic_transpose(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                     int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i * cs_d] = src[i * rs_s + j * cs_s];
        }
    }
}

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

    if (cs_s == 1 && cs_d == 1) {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else if (cs_s == 1 && rs_d == 1) {
        memcpy(dst, src, sizeof(float) * m * n);
    } else if (cs_s == 1 && (rs_d > 1 && cs_d > 1)) {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else if (rs_s == 1 && cs_d == 1) {
        memcpy(dst, src, sizeof(float) * m * n);
    } else if (rs_s == 1 && rs_d == 1) {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else if (rs_s == 1 && (rs_d > 1 && cs_d > 1)) {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else if ((rs_d > 1 && cs_d > 1) && cs_d == 1) {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else if ((rs_d > 1 && cs_d > 1) && rs_d == 1) {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else {
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    }
}
