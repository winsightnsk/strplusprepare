#include "s21_strrchr.h"

char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  int flag = 0;  // если найдено сопадение
  for (s21_size_t i = s21_strlen(str); (int)i >= 0 && !flag; i--) {
    if (str[i] == (char)c) {
      res = (char *)str + i;
      flag = 1;
    }
  }
  return res;
}