#include "spec_f.h"

void specF(char *str, double arg, int *shiftStr, Spec *spec) {
  if (spec->accuracy == 0) {
    spec->accuracy = 6;
  }
  s21_size_t sz = double_counter(arg, spec->accuracy);
  char str_arg[sz + 1];
  for (s21_size_t i = 0; i < sz; i++) {
    str_arg[i] = '*';
  }
  str_arg[sz] = '\0';
  if (arg < 0) {
    str_arg[0] = '-';
    arg = -arg;
  }
  int even_part = (int)arg;
  double fractal = arg - even_part;

  str_arg[sz - spec->accuracy - 1] = '.';
  int p = sz - spec->accuracy;
  for (int i = 1; i <= spec->accuracy; i++) {
    fractal = fractal * 10;
    str_arg[p++] = (int)(fractal + 1e-9) + '0';
    fractal = fractal - (int)(fractal + 1e-9);
  }

  p = sz - spec->accuracy - 2;
  int flag = 1;
  while (flag) {
    str_arg[p--] = even_part % 10 + '0';
    even_part = even_part / 10;
    if (even_part == 0) {
      flag = 0;
    }
  }
  specS(str, str_arg, shiftStr, spec);
}

s21_size_t double_counter(double arg, s21_size_t accuracy) {
  s21_size_t res = 0;
  int even_num = (int)arg;
  if (even_num < 0) {
    res = 1;
    even_num = -even_num;
  }
  if (even_num == 0) {
    res += 2;
  } else {
    while (even_num > 0) {
      even_num = even_num / 10;
      res += 1;
    }
    res += 1;
  }
  return (res + accuracy);
}