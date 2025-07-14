#include "spec_f.h"

void specF(char* str, double arg, int* shiftStr, const s21_size_t width) {
  *shiftStr = 0;
  char str_arg[double_counter(arg)];

}

s21_size_t double_counter(double arg) {
  s21_size_t res = 0;
  int even_num = (int)arg;
  if (even_num < 0) {
    res = 1;
    even_num = -even_num;
  }
  if (even_num == 0) {
    res += 2;
  } else {
    while (even_num > 0) {
      even_num = even_num / 10;
      res += 1;
    }
    res += 1;
  }
  return res + 6;
}