#ifndef SET_SPECS_H
#define SET_SPECS_H

#include <stdarg.h>

#include "struct.h"

const char *set_specs(Spec *specs, const char *format, va_list *args);

#endif