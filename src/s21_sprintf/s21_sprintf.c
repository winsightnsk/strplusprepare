#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  char* startStr = str;
  s21_size_t ptr = 0;

  va_list args;
  va_start(args, format);

  while (format[ptr]) {
    if (format[ptr] == '%') {
      ptr++;
      Spec specs = {0};
      set_specs(&specs, format, &ptr);
      int shiftPtr = 0;
      int shiftStr = 0;

      if (format[ptr] == 'c') specC(str, va_arg(args, int), &shiftStr, &specs);
      if (format[ptr] == 's')
        specS(str, va_arg(args, char*), &shiftStr, &specs);
      if (format[ptr] == 'f')
        specF(str, va_arg(args, double), &shiftStr, &specs);

      ptr += shiftPtr;
      str += shiftStr;
    } else {
      *str = format[ptr];
      str++;
    }
    ptr++;
  }
  *str = '\0';

  va_end(args);

  return str - startStr;  // char* document = va_arg(args, char*);
}
// Число записанных символов или -1, если произошла ошибка.
// Если buffer или format является пустым указателем,
// вызывается обработчик недопустимых параметров,
// как описано в разделе проверки параметров.
// Если разрешается продолжать выполнение,
// эти функции возвращают -1 и задают errno значение EINVAL.

// sprintf возвращает число байтов,
// сохраненных в buffer без учета завершающего символа null.

// int validate(char* data) {
//     int validation_result = !strcmp(data, Available_document);
//     return validation_result;
// }

// int* check_available_documentation_module(int (*validate)(char*), int
// document_count, ...) {
//     int* results = (int*)malloc(document_count * sizeof(int));

//     va_list args;
//     va_start(args, document_count);
//     for (int i = 0; i < document_count; i++) {
//         char* document = va_arg(args, char*);
//         results[i] = validate(document);
//     }
//     va_end(args);

//     return results;
// }