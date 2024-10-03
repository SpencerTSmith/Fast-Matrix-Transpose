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

void simd_8x8_transpose(float *src, float *dst) {
  __m256 r0 = _mm256_loadu_ps(&src[0]);
  __m256 r1 = _mm256_loadu_ps(&src[0 + 8]);
  __m256 r2 = _mm256_loadu_ps(&src[0 + 16]);
  __m256 r3 = _mm256_loadu_ps(&src[0 + 24]);
  __m256 r4 = _mm256_loadu_ps(&src[0 + 32]);
  __m256 r5 = _mm256_loadu_ps(&src[0 + 40]);
  __m256 r6 = _mm256_loadu_ps(&src[0 + 48]);
  __m256 r7 = _mm256_loadu_ps(&src[0 + 56]);

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
}

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst,
              int rs_d, int cs_d) {

  if (m == KERNEL_SIZE ||
      n == KERNEL_SIZE) { // for now just making sure kernel works
    simd_4x4_transpose(src, dst, 0, 0);
  }
}
