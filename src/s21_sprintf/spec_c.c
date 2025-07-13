#include "spec_c.h"

void specC(char* str, char arg, int* shiftStr, const int width) {
  for (int i = 0; i < width-1; i++) {
    *(str + *shiftStr) = ' ';
    *shiftStr++;
  }
  *(str + *shiftStr)  = arg;
  *shiftStr++;
}