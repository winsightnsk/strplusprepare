#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <ctype.h>
#include <stdarg.h>

#include "../common/basetypes.h"
#include "format_width.h"
#include "spec_c.h"
#include "spec_s.h"

int s21_sprintf(char *str, const char *format, ...);

#endif