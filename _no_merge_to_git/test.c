#include "test.h"

#include <string.h>

int main() {
    printf("%s\n", "START");
    char *str = "Hello, world!";
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
        s21_memchr(str, (int)str[i], s21_strlen(str));
    }
    char str1[100] = "Это боль";
    char str2[100] = "всё переделывать aaaaaaaaaaaaaaa";
    s21_memcmp(str2, str1, s21_strlen(str1));
    s21_memcpy(str2, str1, 1);
    s21_memset(str2, '!', 2);
    s21_sprintf(str2, "%c", '_');
    s21_sprintf(str2, "%3c", '!');
    s21_sprintf(str2, "%-3c", '!');
    s21_sprintf(str2, " %s", "Bb");
    s21_sprintf(str2, "1%3s", "L");
    s21_sprintf(str2, "1%-5s2", "!L");
    s21_sprintf(str2, "a, %f, c", 3.001);
    s21_sprintf(str2, "a, %+f, c", 3.001);
    s21_sprintf(str2, "_%d", 123);
    s21_sprintf(str2, "_%ld_", 123456789L);

    s21_strchr(str2, ' ');
    s21_strcspn(str2, " ");
    s21_strerror(8);
    s21_strncat(str2, str1, 1);
    s21_strncmp(str2, str1, 6);
    s21_strncpy(str2, str1, 6);
    s21_strpbrk(str2, " ");
    s21_strrchr(str2, ' ');
    s21_strstr(str2, " ");
    s21_strtok(str2, " ");
    printf("%s - %s\n", str1, str2);
    char* result = s21_to_upper(str2);
    printf("%s\n", result);
    free(result);
    result = s21_to_lower("END");
    free(result);
    result = s21_trim(str2, "Э");
    free(result);
    result = s21_insert("aaabbb", " ", 3);
    free(result);

    char* str3 = "dfdfdfdfdfdfdfdf";
    sprintf(str3, "%-3c", '!');

    return 0;
}