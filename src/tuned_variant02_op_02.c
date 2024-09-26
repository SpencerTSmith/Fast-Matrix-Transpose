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

typedef enum { ROW, COL, GEN, NUM_STRIDE } order_e;

typedef enum {
    ROW_ROW,
    ROW_COL,
    ROW_GEN,
    COL_ROW,
    COL_COL,
    COL_GEN,
    GEN_ROW,
    GEN_COL,
    GEN_GEN,
    NUM_DISPATCH
} dispatch_e;

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

    order_e src_stride = cs_s == 1 ? ROW : rs_s == 1 ? COL : GEN;
    order_e dst_stride = cs_d == 1 ? ROW : rs_d == 1 ? COL : GEN;

    dispatch_e dipatch = src_stride * NUM_STRIDE + dst_stride;

    switch (dipatch) {
    case ROW_ROW:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case ROW_COL:
        memcpy(dst, src, sizeof(float) * m * n);
        break;
    case ROW_GEN:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case COL_ROW:
        memcpy(dst, src, sizeof(float) * m * n);
        break;
    case COL_COL:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case COL_GEN:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case GEN_ROW:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case GEN_COL:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case GEN_GEN:
        basic_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case NUM_DISPATCH: // really should not be possible to be here
        break;
    default: // or here
        fprintf(stderr, "Invalid strides, dispatch not possible");
        break;
    }
}
