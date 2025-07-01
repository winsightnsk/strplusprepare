#include "s21_strstr.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  if (s21_strlen(needle) == 0) {
    result = (char *)haystack;
  }
  for (s21_size_t i = 0; haystack[i] != '\0' && !result; i++) {
    if (haystack[i] == needle[0]) {
      result = (char *)haystack + i;
      for (s21_size_t j = 1; j < s21_strlen(needle) && result; j++) {
        if (haystack[i + j] != needle[j]) {
          result = s21_NULL;
        }
      }
    }
  }
  return result;
}