#include <immintrin.h>
#include <stdio.h>
#include <string.h>

#ifndef FUN_NAME
#define FUN_NAME master
#endif

#define BLOCK_SIZE 32
#define THREAD_SIZE 512
#define KERNEL_SIZE 8

// dispatching help, allows dispatch to be nice switch statement
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

// Prototypes..
// clang-format off
void blocked_transpose_ROW_ROW(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void blocked_transpose_ROW_ROW_omp(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void blocked_transpose_COL_COL(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void blocked_transpose_COL_COL_omp(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void transpose_ROW_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void transpose_COL_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void transpose_GEN_ROW(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void transpose_GEN_COL(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
void transpose_GEN_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d);
// clang-format on

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

    order_e src_order = cs_s == 1 ? ROW : rs_s == 1 ? COL : GEN;
    order_e dst_order = cs_d == 1 ? ROW : rs_d == 1 ? COL : GEN;

    dispatch_e dipatch = src_order * NUM_STRIDE + dst_order;

    // NOTE(spencer): I think that this is more readable than if statements
    switch (dipatch) {
    case ROW_ROW:
        if (m >= THREAD_SIZE * 2 || n >= THREAD_SIZE * 2)
            blocked_transpose_ROW_ROW_omp(m, n, src, rs_s, cs_s, dst, rs_d,
                                          cs_d);
        else
            blocked_transpose_ROW_ROW(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
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
        if (m >= THREAD_SIZE * 2 || n >= THREAD_SIZE * 2)
            blocked_transpose_COL_COL_omp(m, n, src, rs_s, cs_s, dst, rs_d,
                                          cs_d);
        else
            blocked_transpose_COL_COL(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
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

void transpose_ROW_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; i += BLOCK_SIZE) {
        int block_m = (i + BLOCK_SIZE > m) ? (m - i) : BLOCK_SIZE;

        for (int j = 0; j < n; j += BLOCK_SIZE) {
            int block_n = (j + BLOCK_SIZE > n) ? (n - j) : BLOCK_SIZE;

            for (int k = 0; k < block_m; ++k) {
                for (int l = 0; l < block_n; ++l) {
                    dst[(j + l) * rs_d + (i + k) * cs_d] =
                        src[(i + k) * rs_s + (j + l)];
                }
            }
        }
    }
}

void transpose_COL_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    // cols first since contiguous in src
    for (int j = 0; j < n; j += BLOCK_SIZE) {
        int block_n = (j + BLOCK_SIZE > n) ? (n - j) : BLOCK_SIZE;

        for (int i = 0; i < m; i += BLOCK_SIZE) {
            int block_m = (i + BLOCK_SIZE > m) ? (m - i) : BLOCK_SIZE;

            for (int l = 0; l < block_n; ++l) {
                for (int k = 0; k < block_m; ++k) {
                    dst[(j + l) * rs_d + (i + k) * cs_d] =
                        src[(i + k) + (j + l) * cs_s];
                }
            }
        }
    }
}

void transpose_GEN_ROW(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {
    for (int i = 0; i < m; i += BLOCK_SIZE) {
        int block_m = (i + BLOCK_SIZE > m) ? (m - i) : BLOCK_SIZE;

        for (int j = 0; j < n; j += BLOCK_SIZE) {
            int block_n = (j + BLOCK_SIZE > n) ? (n - j) : BLOCK_SIZE;

            for (int k = 0; k < block_m; ++k) {
                for (int l = 0; l < block_n; ++l) {
                    dst[(j + l) * rs_d + (i + k)] =
                        src[(i + k) * rs_s + (j + l) * cs_s];
                }
            }
        }
    }
}

void transpose_GEN_COL(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {

    // cols first since contiguous in dst
    for (int j = 0; j < n; j += BLOCK_SIZE) {
        int block_n = (j + BLOCK_SIZE > n) ? (n - j) : BLOCK_SIZE;

        for (int i = 0; i < m; i += BLOCK_SIZE) {
            int block_m = (i + BLOCK_SIZE > m) ? (m - i) : BLOCK_SIZE;

            for (int l = 0; l < block_n; ++l) {
                for (int k = 0; k < block_m; ++k) {
                    dst[(j + l) + (i + k) * cs_s] =
                        src[(i + k) * rs_s + (j + l) * cs_s];
                }
            }
        }
    }
}

void transpose_GEN_GEN(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                       int rs_d, int cs_d) {

    for (int i = 0; i < m; i += BLOCK_SIZE) {
        int block_m = (i + BLOCK_SIZE > m) ? (m - i) : BLOCK_SIZE;

        for (int j = 0; j < n; j += BLOCK_SIZE) {
            int block_n = (j + BLOCK_SIZE > n) ? (n - j) : BLOCK_SIZE;

            for (int k = 0; k < block_m; ++k) {
                for (int l = 0; l < block_n; ++l) {
                    dst[(j + l) * rs_d + (i + k) * cs_d] =
                        src[(i + k) * rs_s + (j + l) * cs_s];
                }
            }
        }
    }
}

void simd_8x8_transpose(float *src, float *dst, int i, int j, int r_stride,
                        int c_stride) {

    // TODO(spencer): could maybe look into making this branchless,
    // but most likely compiler will generate cmp and move instruction
    // anyways
    int stride = r_stride > c_stride ? r_stride : c_stride;
    __m256 r0 = _mm256_loadu_ps(&src[i * stride + j]);
    __m256 r1 = _mm256_loadu_ps(&src[(i + 1) * stride + j]);
    __m256 r2 = _mm256_loadu_ps(&src[(i + 2) * stride + j]);
    __m256 r3 = _mm256_loadu_ps(&src[(i + 3) * stride + j]);
    __m256 r4 = _mm256_loadu_ps(&src[(i + 4) * stride + j]);
    __m256 r5 = _mm256_loadu_ps(&src[(i + 5) * stride + j]);
    __m256 r6 = _mm256_loadu_ps(&src[(i + 6) * stride + j]);
    __m256 r7 = _mm256_loadu_ps(&src[(i + 7) * stride + j]);

    // this interleaves them so that pairs are now adjacent
    // as they would be if transposed
    __m256 t00 = _mm256_unpacklo_ps(r0, r1);
    __m256 t01 = _mm256_unpackhi_ps(r0, r1);
    __m256 t02 = _mm256_unpacklo_ps(r2, r3);
    __m256 t03 = _mm256_unpackhi_ps(r2, r3);
    __m256 t04 = _mm256_unpacklo_ps(r4, r5);
    __m256 t05 = _mm256_unpackhi_ps(r4, r5);
    __m256 t06 = _mm256_unpacklo_ps(r6, r7);
    __m256 t07 = _mm256_unpackhi_ps(r6, r7);

    // this interleaves it so that quads are now adjacent
    // as they would be if transposed
    __m256 t10 = _mm256_shuffle_ps(t00, t02, 0b01000100);
    __m256 t11 = _mm256_shuffle_ps(t00, t02, 0b11101110);
    __m256 t12 = _mm256_shuffle_ps(t01, t03, 0b01000100);
    __m256 t13 = _mm256_shuffle_ps(t01, t03, 0b11101110);
    __m256 t14 = _mm256_shuffle_ps(t04, t06, 0b01000100);
    __m256 t15 = _mm256_shuffle_ps(t04, t06, 0b11101110);
    __m256 t16 = _mm256_shuffle_ps(t05, t07, 0b01000100);
    __m256 t17 = _mm256_shuffle_ps(t05, t07, 0b11101110);

    // finally interleaves the quads into correct position
    // we can reuse the old temp registers since we don't need them now
    t00 = _mm256_permute2f128_ps(t10, t14, 0b00100000);
    t01 = _mm256_permute2f128_ps(t11, t15, 0b00100000);
    t02 = _mm256_permute2f128_ps(t12, t16, 0b00100000);
    t03 = _mm256_permute2f128_ps(t13, t17, 0b00100000);
    t04 = _mm256_permute2f128_ps(t10, t14, 0b00110001);
    t05 = _mm256_permute2f128_ps(t11, t15, 0b00110001);
    t06 = _mm256_permute2f128_ps(t12, t16, 0b00110001);
    t07 = _mm256_permute2f128_ps(t13, t17, 0b00110001);

    _mm256_storeu_ps(&dst[j * stride + i], t00);
    _mm256_storeu_ps(&dst[(j + 1) * stride + i], t01);
    _mm256_storeu_ps(&dst[(j + 2) * stride + i], t02);
    _mm256_storeu_ps(&dst[(j + 3) * stride + i], t03);
    _mm256_storeu_ps(&dst[(j + 4) * stride + i], t04);
    _mm256_storeu_ps(&dst[(j + 5) * stride + i], t05);
    _mm256_storeu_ps(&dst[(j + 6) * stride + i], t06);
    _mm256_storeu_ps(&dst[(j + 7) * stride + i], t07);
}

void blocked_transpose_ROW_ROW(int m, int n, float *src, int rs_s, int cs_s,
                               float *dst, int rs_d, int cs_d) {
    for (int i = 0; i < m; i += BLOCK_SIZE) {
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            int block_m = (i + BLOCK_SIZE > m) ? (m - i) : i + BLOCK_SIZE;
            int block_n = (j + BLOCK_SIZE > n) ? (n - j) : j + BLOCK_SIZE;

            for (int k = i; k < block_m; k += KERNEL_SIZE) {
                for (int l = j; l < block_n; l += KERNEL_SIZE) {
                    simd_8x8_transpose(src, dst, k, l, rs_s, cs_s);
                }
            }
        }
    }
}

void blocked_transpose_ROW_ROW_omp(int m, int n, float *src, int rs_s, int cs_s,
                                   float *dst, int rs_d, int cs_d) {
    printf("ayup\n");
#pragma omp parallel for collapse(2)
    for (int i = 0; i < m; i += THREAD_SIZE) {
        for (int j = 0; j < n; j += THREAD_SIZE) {
            int block_m = (i + THREAD_SIZE > m) ? (m - i) : i + THREAD_SIZE;
            int block_n = (j + THREAD_SIZE > n) ? (n - j) : j + THREAD_SIZE;

            for (int k = i; k < block_m; k += KERNEL_SIZE) {
                for (int l = j; l < block_n; l += KERNEL_SIZE) {
                    simd_8x8_transpose(src, dst, k, l, rs_s, cs_s);
                }
            }
        }
    }

    // do the rest if not in thread blocks
    int remainder_rows = (m / THREAD_SIZE) * THREAD_SIZE;
    int remainder_cols = (n / THREAD_SIZE) * THREAD_SIZE;

    // do the overlapped portion here since contiguous
    for (int i = remainder_rows; i < m; i += KERNEL_SIZE) {
        for (int j = 0; j < n; j += KERNEL_SIZE) {
            simd_8x8_transpose(src, dst, i, j, rs_s, cs_s);
        }
    }

    for (int i = 0; i < remainder_rows; i += KERNEL_SIZE) {
        for (int j = remainder_cols; j < n; j += KERNEL_SIZE) {
            simd_8x8_transpose(src, dst, i, j, rs_s, cs_s);
        }
    }
}

void blocked_transpose_COL_COL(int m, int n, float *src, int rs_s, int cs_s,
                               float *dst, int rs_d, int cs_d) {
    for (int j = 0; j < n; j += BLOCK_SIZE) {
        for (int i = 0; i < m; i += BLOCK_SIZE) {
            int block_n = (j + BLOCK_SIZE > n) ? (n - j) : j + BLOCK_SIZE;
            int block_m = (i + BLOCK_SIZE > m) ? (m - i) : i + BLOCK_SIZE;

            // same idea, cols first since contiguous
            for (int l = j; l < block_n; l += KERNEL_SIZE) {
                for (int k = i; k < block_m; k += KERNEL_SIZE) {
                    simd_8x8_transpose(src, dst, k, l, rs_s, cs_s);
                }
            }
        }
    }
}

void blocked_transpose_COL_COL_omp(int m, int n, float *src, int rs_s, int cs_s,
                                   float *dst, int rs_d, int cs_d) {
#pragma omp parallel for collapse(2)
    for (int j = 0; j < n; j += THREAD_SIZE) {
        for (int i = 0; i < m; i += THREAD_SIZE) {
            int block_n = (j + THREAD_SIZE > n) ? (n - j) : j + THREAD_SIZE;
            int block_m = (i + THREAD_SIZE > m) ? (m - i) : i + THREAD_SIZE;

            // same idea, cols first since contiguous
            for (int l = j; l < block_n; l += KERNEL_SIZE) {
                for (int k = i; k < block_m; k += KERNEL_SIZE) {
                    simd_8x8_transpose(src, dst, k, l, rs_s, cs_s);
                }
            }
        }
    }

    // do the rest if not in thread blocks
    int remainder_rows = (m / THREAD_SIZE) * THREAD_SIZE;
    int remainder_cols = (n / THREAD_SIZE) * THREAD_SIZE;

    for (int j = 0; j < remainder_cols; j += KERNEL_SIZE) {
        for (int i = remainder_rows; i < m; i += KERNEL_SIZE) {
            simd_8x8_transpose(src, dst, i, j, rs_s, cs_s);
        }
    }

    // do the overlapped portion here since contiguous
    for (int j = remainder_cols; j < n; j += KERNEL_SIZE) {
        for (int i = 0; i < m; i += KERNEL_SIZE) {
            simd_8x8_transpose(src, dst, i, j, rs_s, cs_s);
        }
    }
}
