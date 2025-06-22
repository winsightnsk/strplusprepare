#include "s21_memset.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  for (int i = 0; i < n; i++) {
    ((unsigned char *)str)[i] = (unsigned char *)c;
  }
  return str;
}