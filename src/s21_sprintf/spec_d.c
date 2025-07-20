#include "spec_d.h"

void specD(char *str, Spec *specs, va_list *args, int *shiftStr) {
  long int num = 0;
  if (specs->lenght == 1) {
    num = (long int)va_arg(*args, long int);
  } else if (specs->lenght == 2) {
    num = (int)va_arg(*args, int);
  } else {
    num = (int)va_arg(*args, int);
  }
  s21_size_t size_to_decimal = get_size_to_decimal(specs, num);
  if (size_to_decimal > 0) {
    char *str_to_num = malloc(sizeof(char) * size_to_decimal);
    if (!str_to_num) {
      perror("Ошибка malloc");
    } else {
      int i = decimal_to_string(specs, num, str_to_num, size_to_decimal);
      for (int j = i - 1; j >= 0; j--) {
        *(str + *shiftStr) = str_to_num[j];
        *shiftStr = *shiftStr + 1;
      }
      while (i < specs->width) {
        *(str + *shiftStr) = ' ';
        *shiftStr = *shiftStr + 1;
        i++;
      }
      free(str_to_num);
    }
  }
}

s21_size_t get_size_to_decimal(Spec *specs, long int num) {
  s21_size_t result = 0;
  long int copy_num = num;
  if (copy_num < 0) copy_num = -copy_num;
  if (copy_num == 0 && (specs->accuracy || specs->width || specs->space)) {
    result++;
  }
  while (copy_num > 0) {
    copy_num /= 10;
    result++;
  }
  if ((s21_size_t)specs->width > result) result = specs->width;
  if ((s21_size_t)specs->accuracy > result) result = specs->accuracy;
  if (specs->space || specs->plus || num < 0) {
    specs->flag_to_size = 1;
    result++;
  }
  if (copy_num == 0 && result == 0 && !specs->accuracy && !specs->width &&
      !specs->space && !specs->dot) {
    result++;
  }
  return result;
}

int decimal_to_string(Spec *specs, long int num, char *str_to_num,
                      s21_size_t size_to_decimal) {
  int flag = 0;
  if (num < 0) {
    flag = 1;
    num = -num;
  }
  int i = 0;
  long int copy_num = num;
  if ((copy_num == 0 && (specs->width || specs->space) &&
       ((specs->dot && specs->accuracy) || !specs->dot)) ||
      (copy_num == 0 && !specs->accuracy && !specs->width && !specs->space)) {
    str_to_num[i] = '0';
    i++;
    size_to_decimal--;
  }
  while (copy_num && str_to_num && size_to_decimal) {
    char sym = copy_num % 10 + '0';
    str_to_num[i] = sym;
    i++;
    size_to_decimal--;
    copy_num /= 10;
  }
  if (flag) num = -num;
  if (specs->accuracy - i > 0) {
    specs->accuracy -= i;
  } else {
    specs->accuracy = 0;
  }
  while (str_to_num && (size_to_decimal > 0) && specs->accuracy) {
    str_to_num[i] = '0';
    i++;
    size_to_decimal--;
    specs->accuracy--;
  }
  if (specs->space && num >= 0 && size_to_decimal) {
    str_to_num[i] = ' ';
    i++;
    size_to_decimal--;
  }
  if (num < 0 && size_to_decimal) {
    str_to_num[i] = '-';
    i++;
    size_to_decimal--;
  }
  if (num > 0 && specs->plus && size_to_decimal) {
    str_to_num[i] = '+';
    i++;
    size_to_decimal--;
  }
  if (size_to_decimal > 0 && specs->minus == 0) {
    while ((size_to_decimal - specs->flag_to_size > 0) && str_to_num) {
      str_to_num[i] = ' ';
      i++;
      size_to_decimal--;
    }
  }
  return i;
}