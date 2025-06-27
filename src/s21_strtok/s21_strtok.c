#include "s21_strtok.h"

char *s21_strtok(char *str, const char *delim) {
  static char *state;  // хранит состояние
  char *token_start;   // начало токена
  if (str == s21_NULL) str = state;
  while (*str && s21_strchr(delim, *str))  // пропускаем начальные разделители
    str++;
  if (*str == '\0') {
    token_start = s21_NULL;
  } else {
    token_start = str;                      // начало токена
    str = s21_strpbrk(token_start, delim);  // ищем конец токена
    if (str == s21_NULL) {
      state = s21_strchr(token_start, '\0');  // указатель на конец строки
    } else {
      *str = '\0';  // завершаем, если нашли разделитель
      state = str + 1;  // указатель на начало нового токена
    }
  }
  return token_start;
}
