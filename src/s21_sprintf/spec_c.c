#include "spec_c.h"

void backspacesc(char* str, int* shiftStr, const s21_size_t width) {
  if (width > 0)
    for (s21_size_t i = 0; i < width - 1; i++) {
      *(str + *shiftStr) = ' ';
      *shiftStr = *shiftStr + 1;
    }
}

void specC(char* str, char arg, int* shiftStr, const s21_size_t width,
           const int alignleft) {
  if (!alignleft) backspacesc(str, shiftStr, width);
  *(str + *shiftStr) = arg;
  *shiftStr = *shiftStr + 1;
  if (alignleft) backspacesc(str, shiftStr, width);
}