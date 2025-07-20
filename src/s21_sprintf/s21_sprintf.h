#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <ctype.h>
#include <stdarg.h>

#include "../common/basetypes.h"
#include "set_specs.h"
#include "spec_c.h"
#include "spec_d.h"
#include "spec_f.h"
#include "spec_s.h"

int s21_sprintf(char *str, const char *format, ...);

#endif