#include "spec_c.h"

void backspacesc(char* str, int* shiftStr, const s21_size_t width) {
  if (width > 0)
    for (s21_size_t i = 0; i < width - 1; i++) {
      *(str + *shiftStr) = ' ';
      *shiftStr = *shiftStr + 1;
    }
}

void specC(char* str, char arg, int* shiftStr, const Spec* spec) {
  if (!spec->minus) backspacesc(str, shiftStr, spec->width);
  *(str + *shiftStr) = arg;
  *shiftStr = *shiftStr + 1;
  if (spec->minus) backspacesc(str, shiftStr, spec->width);
}