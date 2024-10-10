#include <string.h>
#ifndef FUN_NAME
#define FUN_NAME optimized_double_blocked_transpose
#endif

// Change block size for analysis
#define BLOCK_SIZE 32 // Outer block size determined from variation 10
#define INNER_BLOCK_SIZE 4 

void basic_transpose(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            dst[j * rs_d + i * cs_d] = src[i * rs_s + j * cs_s];
        }
    }
}

// Double blocked transpose
void double_blocked_transpose(int m, int n, float *src, int rs_s, int cs_s, float *dst,
                               int rs_d, int cs_d) {
    for (int i = 0; i < m; i += BLOCK_SIZE) { // Outer block iteration over rows
        for (int j = 0; j < n; j += BLOCK_SIZE) { // Outer block iteration over columns
            // Inner block iteration
            for (int ii = i; ii < i + BLOCK_SIZE && ii < m; ii += INNER_BLOCK_SIZE) {
                for (int jj = j; jj < j + BLOCK_SIZE && jj < n; jj += INNER_BLOCK_SIZE) {
                    // Process inner block
                    for (int k = 0; k < INNER_BLOCK_SIZE && (ii + k) < m; ++k) {
                        for (int l = 0; l < INNER_BLOCK_SIZE && (jj + l) < n; ++l) {
                            dst[(jj + l) * rs_d + (ii + k) * cs_d] = src[(ii + k) * rs_s + (jj + l) * cs_s];
                        }
                    }
                }
            }
        }
    }
}

int calculate_optimal_block_size(int cache_size, int element_size) {
    return (cache_size / element_size) / 2; // Divided by 2 for some overhead
}

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

    int cache_size = 16384 * 1024; // Cache size in bytes
    int element_size = sizeof(float);
    int optimal_block_size = calculate_optimal_block_size(cache_size, element_size);

    // Choose which transpose function to use based on matrix size and block size
    if (m > optimal_block_size || n > optimal_block_size) {
        double_blocked_transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
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
