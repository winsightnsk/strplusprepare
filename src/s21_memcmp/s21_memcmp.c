#include "s21_memcmp.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (((unsigned char *)str1)[i] > ((unsigned char *)str2)[i]) {
      result++;
      i = n;
    } else if (((unsigned char *)str1)[i] < ((unsigned char *)str2)[i]) {
      result--;
      i = n;
    }
  }
  return result;
}