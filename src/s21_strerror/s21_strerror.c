#include "s21_strerror.h"

#include <stdio.h>

char *s21_strerror(int errnum) {
  char *res = s21_NULL;
  printf("%s\n", ERRORS[errnum]);
  //s21_strncpy(res, LINUX_ERRORS[errnum], s21_strlen(LINUX_ERRORS[errnum]));
  return res;
}