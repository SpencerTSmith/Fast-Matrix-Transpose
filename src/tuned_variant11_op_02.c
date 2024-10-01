#include <immintrin.h>
#ifndef FUN_NAME
#define FUN_NAME baseline_transpose
#endif

#define KERNEL_SIZE 4

void simd_4x4_transpose(float *src, float *dst, int i, int j) {
    __m256 input00_07 = _mm256_loadu_ps(&src[i]);
    __m256 input08_15 = _mm256_loadu_ps(&src[i + 8]);
    __m256 temp0 = _mm256_shuffle_ps(input00_07, input08_15, 0b01000100);
    __m256 temp1 = _mm256_shuffle_ps(input00_07, input08_15, 0b11101110);

    __m256i index = _mm256_setr_epi32(0, 4, 2, 6, 1, 5, 3, 7);
    __m256 output00_07 = _mm256_permutevar8x32_ps(temp0, index);
    __m256 output08_15 = _mm256_permutevar8x32_ps(temp1, index);
    _mm256_storeu_ps(&dst[i], output00_07);
    _mm256_storeu_ps(&dst[i + 8], output08_15);
}

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

    if (m == KERNEL_SIZE ||
        n == KERNEL_SIZE) { // for now just making sure kernel works
        simd_4x4_transpose(src, dst, 0, 0);
    }
}
