#include "get_specs.h"

const char *get_specs(const char *format, Spec *specs) {
    while(format) {
        if (*format == '+')
        specs->plus = 1;
        else if (*format == '-')
        specs->minus = 1;
        // else if (*format == '#')
        // specs->hash = 1;
        else if (*format == ' ')
        specs->space = 1;
        // else if (*format == '0')
        // specs->zero = 1;
        else 
        break;
        format++;
    }
    specs->space = (specs->space && !specs->plus);
    // specs->zero = (specs->space && !specs->minus);
    return format;    
}
