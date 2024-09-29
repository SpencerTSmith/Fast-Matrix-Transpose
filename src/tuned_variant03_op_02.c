#include <stdio.h>
#include <string.h>
#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

// Specific functions, for now just eliminating superfluous multiplies
void transpose_GEN_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i * cs_d] = src[i * rs_s + j * cs_s];
        }
    }
}

void transpose_ROW_ROW(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i] = src[i * rs_s + j];
        }
    }
}

void transpose_ROW_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i * cs_d] = src[i * rs_s + j];
        }
    }
}

void transpose_COL_COL(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j + i * cs_d] = src[i + j * cs_s];
        }
    }
}

void transpose_COL_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i * cs_d] = src[i + j * cs_s];
        }
    }
}

void transpose_GEN_ROW(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i] = src[i * rs_s + j * cs_s];
        }
    }
}

void transpose_GEN_COL(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j + i * cs_s] = src[i * rs_s + j * cs_s];
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

    order_e src_order = cs_s == 1 ? ROW : rs_s == 1 ? COL : GEN;
    order_e dst_order = cs_d == 1 ? ROW : rs_d == 1 ? COL : GEN;

    dispatch_e dipatch = src_order * NUM_STRIDE + dst_order;

    switch (dipatch) {
    case ROW_ROW:
        transpose_ROW_ROW(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case ROW_COL:
        memcpy(dst, src, sizeof(float) * m * n);
        break;
    case ROW_GEN:
        transpose_ROW_GEN(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case COL_ROW:
        memcpy(dst, src, sizeof(float) * m * n);
        break;
    case COL_COL:
        transpose_COL_COL(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case COL_GEN:
        transpose_COL_GEN(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case GEN_ROW:
        transpose_GEN_ROW(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case GEN_COL:
        transpose_GEN_COL(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case GEN_GEN:
        transpose_GEN_GEN(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
        break;
    case NUM_DISPATCH: // really should not be possible to be here
        fprintf(stderr, "Invalid strides, dispatch not possible");
        break;
    default: // or here
        fprintf(stderr, "Invalid strides, dispatch not possible");
        break;
    }
}
