#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

#include "../common/basetypes.h"
#include "spec_c.h"
#include "spec_s.h"
#include "spec_f.h"

int s21_sprintf(char *str, const char *format, ...);

#endif