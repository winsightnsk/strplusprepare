#include "s21_strncpy.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  // Копируем из src в dest, пока не достигнем n или не дойдем до конца src
  for (; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  // Если скопировали меньше n, заполняем ставшиеся \0
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}