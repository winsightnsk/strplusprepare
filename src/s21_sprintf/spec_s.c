#include "spec_s.h"

void specS(char* str, char* arg, int* shiftStr, int* shiftPtr) {
  *shiftPtr = 0;
  *shiftStr = 0;
  for (; *arg; arg++, str++) {
    *str = *arg;
    *shiftStr += 1;
  }
}