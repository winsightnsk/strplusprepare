#ifndef SET_SPECS_H
#define SET_SPECS_H

#include "../common/basetypes.h"
#include "struct.h"

void set_specs(Spec *specs, const char *format, s21_size_t *ptr);
void get_specs(const char *format, s21_size_t *ptr, Spec *specs);
void get_wigth(const char *format, int *wight, s21_size_t *ptr);

#endif