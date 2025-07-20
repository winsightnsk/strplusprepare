#include "s21_trim.h"
// #include <stdio.h>

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (src != s21_NULL) {
    s21_size_t length_src = s21_strlen(src);
    s21_size_t length_trim = s21_strlen(trim_chars);
    s21_size_t start_index = 0;
    s21_size_t finish_index = 0;
    for (s21_size_t i = 0; i <= length_src; i++) {
      for (s21_size_t j = 0; j < length_trim; j++) {
        if (src[i] == trim_chars[j]) {
          break;
        } else if (j == length_trim - 1) {
          start_index = i;
        }
      }
      if (start_index) break;
    }
    // printf("%ld - ", start_index);
    for (int i = length_src - 1; i > 0; i--) {
      for (int j = 0; j < (int)length_trim; j++) {
        if (src[i] == trim_chars[j]) {
          break;
        } else if (j == (int)length_trim - 1) {
          finish_index = i;
        }
      }
      if (finish_index) break;
    }
    // printf("%ld\n", finish_index);
    if (start_index >= finish_index) {
      result = malloc(1);
      if (result != s21_NULL) {
        result[0] = '\0';
      }
    } else {
      result = malloc(finish_index - start_index + 1);
      if (result != s21_NULL) {
        s21_size_t i_res = 0;
        for (s21_size_t i = start_index; i <= finish_index; i++) {
          result[i_res] = src[i];
          i_res++;
        }
      }
    }
  }
  return result;
}
