#include "s21_strpbrk.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  int flag = 0;  // флаг если нашел первый символ из str2
  for (int i = 0; str1[i] != '\0' && !flag; i++) {
    for (int j = 0; str2[j] != '\0' && !flag; j++) {
      if (str1[i] == str2[j]) {
        res = (char *)str1 + i;
        flag = 1;
      }
    }
  }
  return res;
}