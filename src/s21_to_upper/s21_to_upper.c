#include "s21_to_upper.h"

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t length = s21_strlen(str);
    result = malloc(length + 1);
    if (result != s21_NULL) {
      for (s21_size_t i = 0; i <= length; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
          result[i] = str[i] + 'A' - 'a';
        else
          result[i] = str[i];
      }
    }
  }
  return result;
}