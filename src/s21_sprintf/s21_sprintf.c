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

      if (format[ptr] == 'c' && (!specs.lng))
        specC(str, va_arg(args, int), &shiftStr, &specs);
      if (format[ptr] == 'c' && specs.lng)
        specLC(str, va_arg(args, wchar_t), &shiftStr, &specs);
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


sprintf(buffer, "_%lc_", ch);
В языке Си функция sprintf с форматом %lc используется для записи широкого символа (wide character, wchar_t) в строку в виде многобайтовой последовательности (если это необходимо).

Разбор примера: sprintf(buffer, "_%lc_", ch);
1. Что делает %lc?
%lc ожидает аргумент типа wchar_t (широкий символ) и преобразует его в многобайтовую последовательность (если требуется).

Если локаль (locale) настроена на UTF-8 или другую многобайтовую кодировку, то символ может занимать больше 1 байта.

Если ch — обычный char, поведение не определено (UB), так как %lc требует wchar_t.

2. Пример корректного использования
c
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");  // Устанавливаем локаль (для корректного преобразования)

    wchar_t ch = L'Я';      // Широкий символ (например, кириллическая 'Я')
    char buffer[100];

    sprintf(buffer, "_%lc_", ch);  // Преобразует wchar_t в многобайтовую строку
    printf("Результат: %s\n", buffer);  // Выведет что-то вроде: "_Я_"

    return 0;
}
3. Возможные проблемы
Если не установлена локаль

Без setlocale(LC_ALL, "") преобразование может работать некорректно (например, выведет _?_ вместо кириллицы).

Если передать char вместо wchar_t

c
char ch = 'A';  // Обычный char
sprintf(buffer, "_%lc_", ch);  // Неопределённое поведение (UB)!
Нужно использовать %c для char и %lc только для wchar_t.

4. Альтернативы (если не нужны широкие символы)
Если вам нужно просто записать char в строку, используйте %c:

c
char ch = 'A';
sprintf(buffer, "_%c_", ch);  // Корректно: "_A_"
Вывод
%lc в sprintf предназначен только для wchar_t.

Требует правильной локали (setlocale).

Для обычных char используйте %c.

Если локаль не поддерживает символ, может произойти ошибка преобразования.

Если вам нужно работать с Unicode-символами, лучше использовать wchar_t и %lc. Для ASCII-символов достаточно %c.

Вот реализация функции s21_sprintf, которая обрабатывает формат "_%lc_" аналогично стандартной sprintf:

c
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

// Упрощённая версия sprintf для формата "_%lc_"
int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;
    const char *f = format;

    while (*f) {
        if (*f != '%') {
            *str++ = *f++;
            written++;
            continue;
        }

        // Обработка '%'
        f++;
        if (*f == 'l') {
            f++;
            if (*f == 'c') {
                // Обработка %lc
                wchar_t wc = va_arg(args, wchar_t);
                char mb[MB_CUR_MAX];
                int len = wctomb(mb, wc);
                if (len > 0) {
                    memcpy(str, mb, len);
                    str += len;
                    written += len;
                }
                f++;
            }
        }
    }

    *str = '\0';
    va_end(args);
    return written;
}

int main() {
    setlocale(LC_ALL, ""); // Важно для корректного преобразования широких символов

    char buffer[100];
    wchar_t wide_char = L'Я'; // Широкий символ

    s21_sprintf(buffer, "_%lc_", wide_char);
    printf("Результат: %s\n", buffer); // Должно вывести "_Я_"

    return 0;
}
Ключевые моменты реализации:
Обработка varargs:

Используем va_list для работы с переменным числом аргументов

va_arg(args, wchar_t) получает широкий символ из аргументов

Преобразование широкого символа:

wctomb() конвертирует широкий символ в многобайтовую последовательность

MB_CUR_MAX - максимальная длина многобайтового символа в текущей локали

Безопасность:

Проверяем успешность преобразования (len > 0)

Всегда завершаем строку нуль-терминатором

Локализация:

setlocale(LC_ALL, "") критически важна для правильной работы с широкими символами

Эта реализация специально упрощена для формата "%lc". Полная версия sprintf должна обрабатывать все спецификаторы формата, флаги, ширину и точность.

Вот реализация функции s21_sprintf, которая обрабатывает формат "_%5lc_" с указанием минимальной ширины поля (5 символов), аналогично стандартной sprintf:

c
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;
    const char *f = format;

    while (*f) {
        if (*f != '%') {
            *str++ = *f++;
            written++;
            continue;
        }

        // Обработка '%'
        f++;

        // Парсинг ширины поля
        int width = 0;
        while (*f >= '0' && *f <= '9') {
            width = width * 10 + (*f - '0');
            f++;
        }

        if (*f == 'l') {
            f++;
            if (*f == 'c') {
                // Обработка %lc с шириной
                wchar_t wc = va_arg(args, wchar_t);
                char mb[MB_CUR_MAX];
                int len = wctomb(mb, wc);

                // Добавление пробелов для достижения ширины
                int padding = width - len;
                if (padding > 0) {
                    memset(str, ' ', padding);
                    str += padding;
                    written += padding;
                }

                if (len > 0) {
                    memcpy(str, mb, len);
                    str += len;
                    written += len;
                }
                f++;
            }
        }
    }

    *str = '\0';
    va_end(args);
    return written;
}

int main() {
    setlocale(LC_ALL, "");

    char buffer[100];
    wchar_t wide_char = L'Я';

    s21_sprintf(buffer, "_%5lc_", wide_char);
    printf("Результат: '%s'\n", buffer);  // Выведет: '_    Я_'

    // Тест с более коротким символом
    s21_sprintf(buffer, "_%5lc_", L'A');
    printf("Результат: '%s'\n", buffer);  // Выведет: '_    A_'

    return 0;
}
Ключевые особенности:
Обработка ширины поля:

Парсинг числового значения после '%' (в данном случае 5)

Вычисление количества пробелов для дополнения: padding = width - actual_length

Выравнивание по правому краю:

Пробелы добавляются перед символом (стандартное поведение для sprintf)

Для выравнивания по левому краю нужно было бы добавить флаг '-'

Многобайтовая обработка:

Широкий символ конвертируется с учетом текущей локали

Используется wctomb() для правильного преобразования

Особенности вывода:

Если символ занимает 2 байта (например, кириллица в UTF-8), а ширина 5, то будет добавлено 3 пробела

Для ASCII-символов (1 байт) добавится 4 пробела

Эта реализация специально адаптирована под формат %5lc. Полная версия sprintf должна дополнительно обрабатывать:

Флаги ('-', '0', etc.)

Точность

Модификаторы размера

Все спецификаторы преобразования