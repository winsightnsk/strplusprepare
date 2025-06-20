#include "s21_strlen.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str[length] != '\0') { //идем по строке пока не встретим конец строки
    length++;
  }
  return length;
}                                                                                                                   