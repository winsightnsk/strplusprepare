#ifndef SPEC_D_H
#define SPEC_D_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/basetypes.h"
#include "struct.h"

void specD(char *str, Spec *specs, va_list *agrs, int *shiftStr);
s21_size_t get_size_to_decimal(Spec *specs, long int num);
int decimal_to_string(Spec *specs, long int num, char *str_to_num,
                      s21_size_t size_to_decimal);

#endif