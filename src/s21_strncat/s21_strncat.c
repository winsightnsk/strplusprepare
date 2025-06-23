#include "s21_strncat.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = s21_strlen(dest);  // стартовый индекс для вставки в dest
  for (s21_size_t j = 0; j < n && src[j] != '\0'; j++) {
    dest[i] = src[j];
    i++;
  }
  dest[i] = '\0';
  return dest;
}