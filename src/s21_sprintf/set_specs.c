#include "set_specs.h"

void set_specs(Spec *specs, const char *format, s21_size_t *ptr) {
  get_specs(format, ptr, specs);
  get_width(format, &specs->width, ptr);
  if (*(format + *ptr) == '.') {
    specs->dot = 1;
    *ptr += 1;
    get_width(format, &specs->accuracy, ptr);
  }
  if (*(format + *ptr) == 'l')
    specs->lng = 1;
  else if (*(format + *ptr) == 'h')
    specs->lng = 1;
  if (specs->lng != 0) *ptr += 1;
}

void get_specs(const char *format, s21_size_t *ptr, Spec *specs) {
  while (*(format + *ptr)) {
    if (*(format + *ptr) == '+')
      specs->plus = 1;
    else if (*(format + *ptr) == '-')
      specs->minus = 1;
    else if (*(format + *ptr) == ' ')
      specs->space = 1;
    else
      break;
    *ptr += 1;
  }
  specs->space = (specs->space && !specs->plus);
}

void get_width(const char *format, int *width, s21_size_t *ptr) {
  *width = 0;
  for (; isdigit(*(format + *ptr)); *ptr += 1) {
    *width *= 10;
    *width += *(format + *ptr) - '0';
  }
}