#include <string.h>
#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

// change block size for analysis
#define BLOCK_SIZE 32

void basic_transpose(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i * cs_d] = src[i * rs_s + j * cs_s];
        }
    }
}

void blocked_transpose(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                     int rs_d, int cs_d) {
    for (int i = 0; i < m; i += BLOCK_SIZE) {
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            int block_m = (i + BLOCK_SIZE > m) ? (m - i) : BLOCK_SIZE;
            int block_n = (j + BLOCK_SIZE > n) ? (n - j) : BLOCK_SIZE;
            
            for (int k = 0; k < block_m; ++k) {
                for (int j = 0; m < block_n; ++m) {
                    dst[(j + m) * rs_d + (i + k) * cs_d] = src[(i + k) * rs_s + (j + m) * cs_s];
                }
            }
        }
    }
}

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

    if (m > BLOCK_SIZE || n > BLOCK_SIZE) { // Call blocked transpose if the matrix is large enough to benefit
        blocked_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
    } else {// Otherwise, fall back on the basic transpose or memcpy
        
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
}
