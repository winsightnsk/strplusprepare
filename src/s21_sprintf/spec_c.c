#include "spec_c.h"

void specC(char* str, char arg, int* shiftStr, int* shiftPtr) {
  *str = arg;
  *shiftStr = 1;
  *shiftPtr = 0;
}