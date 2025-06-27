#ifndef S21_STRTOK
#define S21_STRTOK

#include "../common/basetypes.h"
#include "../s21_strchr/s21_strchr.h"
#include "../s21_strlen/s21_strlen.h"
#include "../s21_strpbrk/s21_strpbrk.h"

char *s21_strtok(char *str, const char *delim);

#endif