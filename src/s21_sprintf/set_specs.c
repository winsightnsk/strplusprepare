#include "set_specs.h"

void set_specs(Spec *specs, const char *format, s21_size_t *ptr) {
  get_specs(format, ptr, specs);
  get_wigth(format, &specs->wight, ptr);
  if (*(format + *ptr) == '.') {
    specs->dot = 1;
    ptr++;
    get_wigth(format, &specs->accuracy, ptr);
  }
  if (*(format + *ptr) == 'l')
    specs->lenght = 'l';
  else if (*(format + *ptr) == 'h')
    specs->lenght = 'h';
  if (specs->lenght != 0) ptr++;
  // if (specs->wight < 0) {
  //   specs->wight = -specs->wight;
  //   specs->minus = 1;
  // }
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
    ptr++;
  }
  specs->space = (specs->space && !specs->plus);
}

void get_wigth(const char *format, int *wight, s21_size_t *ptr) {
  *wight = 0;
  while (*(format + *ptr)) {
    if ('0' <= *(format + *ptr) && *(format + *ptr) <= '9') {
      *wight *= 10;
      *wight += *(format + *ptr) - '0';
    } else
      break;
    ptr++;
  }
}