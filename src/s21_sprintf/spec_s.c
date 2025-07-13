#include "spec_s.h"

void specS(char* str, char* arg, int* shiftStr, const int width) {
  for (int i = 0; i < width-s21_strlen(arg); i++) {
    *str = ' ';
    str++;
    *shiftStr++;
  }
  for (; *arg; arg++, str++) {
    *str = *arg;
    *shiftStr++;
  }
}