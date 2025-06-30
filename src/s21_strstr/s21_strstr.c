#include "s21_strstr.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  int flag = 0;
  if (s21_strlen(haystack) >= s21_strlen(needle)) {
    result = (char *)haystack;
    flag = 1;
  }
  for (s21_size_t i = 0; i <= s21_strlen(haystack) - s21_strlen(needle) && flag && haystack[i] != '\0'; i++) {
    if (haystack[i] == needle[0]) {
      result = (char *)haystack + i;
      for (s21_size_t j = 0; j < s21_strlen(needle) && !result; j++) {
        if (haystack[i + j] != needle[j]) {
          result = s21_NULL;
        }
        if (j == s21_strlen(needle)) {
          flag = 0;
        }
      }
    }
  }
  return result;
}