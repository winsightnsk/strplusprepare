#include "spec_s.h"

void backspacess(char* str, const char* arg, int* shiftStr,
                 const s21_size_t width) {
  if (width > s21_strlen(arg))
    for (s21_size_t i = 0; i < width - s21_strlen(arg); i++) {
      *(str + *shiftStr) = ' ';
      *shiftStr = *shiftStr + 1;
    }
}

void specS(char* str, char* arg, int* shiftStr, const Spec* spec) {
  if (!spec->minus) backspacess(str, arg, shiftStr, spec->width);
  for (int i = 0; *(arg + i); i++) {
    *(str + *shiftStr) = *(arg + i);
    *shiftStr = *shiftStr + 1;
  }
  if (spec->minus) backspacess(str, arg, shiftStr, spec->width);
}

// for (; *arg; arg++) {
//     *(str + *shiftStr) = *arg;
//     *shiftStr = *shiftStr + 1;
//   }