#include "s21_memchr.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result;
  result = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (*((char *)str + i) == c) {
      result = (char *)str + i;
    }
  }
  return (void *)result;
}