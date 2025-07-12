#include "set_specs.h"

const char * set_specs(Spec*specs, const char *format, va_list *args) {
    format = get_specs(format, specs);
    format = get_width(format, &specs->wight, args);
    if (*format == '.') {
        specs->dot = 1;
        // specs->zero = 0;
        format++;
        format = get_width(format, &specs->accuracy, args);
    } 
    if (*format == 'l')
    specs->lenght = 'l';
    else if (*format == 'h')
    specs->lenght = 'h';
    // else if (*format == 'L')
    // specs->lenght = 'L';
    if (specs->lenght != 0) format++;
    if (specs->wight <0) {
        specs->wight = -specs->wight;
        specs->minus = 1;
    }
    return format;
}