#ifndef SET_SPECS_H
#define SET_SPECS_H

#include <ctype.h>

#include "../common/basetypes.h"
#include "struct.h"

void set_specs(Spec *specs, const char *format, s21_size_t *ptr);
void get_specs(const char *format, s21_size_t *ptr, Spec *specs);
void get_width(const char *format, int *width, s21_size_t *ptr);

#endif