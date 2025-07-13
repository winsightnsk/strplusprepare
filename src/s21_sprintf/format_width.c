#include "format_width.h"

void formatWidth(const char* format, s21_size_t* ptr, s21_size_t* width) {
    for (; isdigit(*(format + *ptr)); *ptr += 1) {
        *width *= 10;
        *width += *(format + *ptr) - '0';
    }
    return shift_ptr;
}