#include "s21_strcspn.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  int flag = 0;  // флаг если нашел символ из str2
  for (s21_size_t i = 0; str1[i] != '\0' && !flag; i++) {
    for (int j = 0; str2[j] != '\0' && !flag; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
        res = i;  // индекс найденного символа равен количеству до
      }
    }
  }
  return (flag == 0) ? s21_strlen(str1) : res;
}