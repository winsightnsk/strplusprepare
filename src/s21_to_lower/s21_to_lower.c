#include "s21_to_lower.h"

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t length = s21_strlen(str);
    result = malloc(length + 1);
    if (result != s21_NULL) {
      for (s21_size_t i = 0; i <= length; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
          result[i] = str[i] - ('A' - 'a');
        else
          result[i] = str[i];
      }
    }
  }
  return result;
}