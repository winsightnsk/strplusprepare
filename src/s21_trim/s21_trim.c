#include "s21_trim.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src != s21_NULL) {
    s21_size_t length = s21_strlen(src);
    result = malloc(length + 1); // From here
    if (result != s21_NULL) {
      for (s21_size_t i = 0; i <= length; i++) {
        if (str[i] == trim_chars[0]) {
          int ptr = i;
          for (s21_size_t j = 0; j <= length; j++) {
            if (str[ptr + j] != trim_chars[j]) {
              i = ptr + j;
              break;
            }
          }
        }
      }
    }
  }
  return result;
}
