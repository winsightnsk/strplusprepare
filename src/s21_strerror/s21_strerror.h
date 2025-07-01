#ifndef S21_STRERROR_H
#define S21_STRERROR_H

#ifdef __APPLE__

#elif __linux__

#endif

#include "../common/basetypes.h"

char *s21_strerror(int);

#endif