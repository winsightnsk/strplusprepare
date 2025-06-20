#include "s21_strncmp.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  // пока не достигли лимита n и строка не закончилась, сравниваем символы
  while (n > 0 && *str1 && (*str1 == *str2)) {
    str1++;
    str2++;
    n--;
  }
  // если равны по первым n символам return 0 иначе разницу кодов символов
  return (n == 0) ? res : ((unsigned char)*str1 - (unsigned char)*str2);
}