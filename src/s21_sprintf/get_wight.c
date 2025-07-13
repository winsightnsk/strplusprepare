#include "get_wight.h"

const char *get_wigth(const char *format, int *wight, va_list *args) {
  *wight = 0;
  // if (*format == '*'){
  //     *wight = va_arg(*args,int);
  //     format++;
  // }
  while (format) {
    if ('0' <= *format && format <= '9') {
      *wight *= 10;
      *wight += *format - '0';
    } else
      break;
    format++;
  }
  return format;
}