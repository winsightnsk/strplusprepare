#include "spec_f.h"

void specF(char* str, double arg, int* shiftStr, int* shiftPtr) {
  *shiftStr = 0;
  *shiftPtr = 0;
  if (arg < 0) {
    *str = '-';
    arg = -arg;
    str++;
    *shiftStr += 1;
  }
  if (arg == 0) {
    for (int i = 0; i < 8; i++) {
      if (i != 1) {
        *str = '0';
      } else {
        *str = '.';
      }
      str++;
      *shiftStr += 1;
    }
  } else {
    // Тут надо написать алгоритм перевода десятичной дроби в текст
    int len = 0;
    int d_arg = (int)arg;
    for (; d_arg > 0; len++, d_arg = d_arg / 10);
    for (int i = 0; i < len; i++) {
      *str = arg / pow(10, len - i - 1) + (int)'0';
      str++;
      *shiftStr += 1;
    }

    *str = '.';
    str++;
    *shiftStr += 1;
    for (int i = 0; i < 6; i++) {
      *str = (int)(arg * 10) % 10 + (int)'0';
      str++;
      *shiftStr += 1;
    }
  }
}