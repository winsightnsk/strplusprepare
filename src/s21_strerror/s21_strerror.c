#include "s21_strerror.h"

char *s21_strerror(int errnum) {
  static char message[50];
  if (errnum > ERR_SIZE || errnum < 0) {
    sprintf(message, STR_ERROR " %d", errnum);
  } else {
    s21_strncpy(message, ERRORS[errnum], 50);
  }
  char *res = message;
  return res;
}