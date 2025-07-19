#ifndef S21_TRIM
#define S21_TRIM

#include <stdlib.h>

#include "../common/basetypes.h"
#include "../s21_strlen/s21_strlen.h"

void *s21_trim(const char *src, const char *trim_chars);

#endif