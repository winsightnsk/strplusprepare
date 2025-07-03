#include "s21_strerror.h"

#include <stdio.h>

char *s21_strerror(int errnum) {
  if (errnum > ERR_SIZE) {
    errnum = 0;
  }
  char *res = (char *)ERRORS[errnum];
  return res;
}