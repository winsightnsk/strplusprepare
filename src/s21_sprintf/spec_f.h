#ifndef SPEC_F_H
#define SPEC_F_H

#include "../common/basetypes.h"
#include "spec_s.h"

void specF(char* str, double arg, int* shiftStr, const s21_size_t width,
           s21_size_t accuracy);
s21_size_t double_counter(double arg, s21_size_t accuracy);

#endif