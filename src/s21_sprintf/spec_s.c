#include "spec_s.h"

void specS(char* str, char* arg, int* shiftStr, const s21_size_t width) {
  if (width > s21_strlen(arg))
    for (s21_size_t i = 0; i < width - s21_strlen(arg); i++) {
      *(str + *shiftStr) = ' ';
      *shiftStr = *shiftStr + 1;
    }
  for (; *arg; arg++) {
    *(str + *shiftStr) = *arg;
    *shiftStr = *shiftStr + 1;
  }
}