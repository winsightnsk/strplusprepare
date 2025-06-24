#include "s21_strchr.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str) + 1; i++) {
    if (str[i] == (char)c) {
      result = (char *)str + i;
      i = s21_strlen(str);
    }
  }
  return result;
}