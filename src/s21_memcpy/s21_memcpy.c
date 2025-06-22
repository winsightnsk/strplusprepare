#include "s21_memcpy.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (int i = 0; i < n; i++) {
    ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
  }
  return dest;
}