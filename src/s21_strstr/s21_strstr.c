#include "s21_strstr.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(haystack) - s21_strlen(needle); i++) {
    if (haystack[i] == needle[0]) {
      result = (char *)haystack + i;
      for (s21_size_t j = 1; j < s21_strlen(needle) - 1; j++) {
        if (haystack[i + j] == needle[j]) {
          result = (char *)haystack + i + j;
        } else {
          result = s21_NULL;
          j = s21_strlen(needle);
        }
      }
    }
  }
  return result;
}