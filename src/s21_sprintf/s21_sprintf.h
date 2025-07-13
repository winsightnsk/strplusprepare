#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>
#include <ctype.h>

#include "../common/basetypes.h"
#include "spec_c.h"
#include "spec_s.h"
#include "format_width.h"

int s21_sprintf(char *str, const char *format, ...);

#endif