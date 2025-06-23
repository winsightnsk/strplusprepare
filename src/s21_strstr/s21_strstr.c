#include "s21_strstr.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(haystack), needle[i] != '\0'; i++) {
    if (haystack[i] == needle[i]) {
      result = (char *)haystack + i;
      for (s21_size_t j = 1; j < s21_strlen(needle), needle[j] != '\0', result; j++) {
        if (haystack[i + j] == needle[j]) {
          result = (char *)haystack + i + j;
        } else { result = s21_NULL; }
      }
    }
  }
  return result;
}