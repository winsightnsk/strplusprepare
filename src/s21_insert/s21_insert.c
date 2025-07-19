#include "s21_insert.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  if (str != s21_NULL && src != s21_NULL && start_index <= s21_strlen(src)) {
    s21_size_t length_src = s21_strlen(src);
    s21_size_t length_str = s21_strlen(str);
    result = malloc(length_src + length_str + 1);
    if (result != s21_NULL) {
      s21_size_t i;
      for (i = 0; i < start_index; i++) {
        result[i] = src[i];
      }
      s21_size_t j;
      for (j = 0; j < length_str; j++) {
        result[i + j] = str[j];
      }
      for (i = start_index; i < length_src; i++) {
        result[i + j] = src[i];
      }
    }
  }
  return result;
}