#include "test.h"

int main() {
    char *result = s21_insert("aaabbb", " ", 3);
    printf("%s\n", result);
    char *str = "Hello, world!";
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
        s21_memchr(str, (int)str[i], s21_strlen(str));
    }
    // char* str1 = "Это боль";
    // char* str2 = "всё переделывать aaaaaaaaaaaaaaa";
    // s21_strlen(str1);
    // s21_memcmp(str2, str1, s21_strlen("11"));
    // s21_memcpy(str2, str1, 1);
    // s21_memset(str2, 'A', 5);
    // s21_sprintf(str2, "a, %c", 'b');
    // s21_sprintf(str2, "%3c", '!');
    // s21_sprintf(str2, "%-3c", '!');
    // s21_sprintf(str2, " %s", "Bb");
    // s21_sprintf(str2, "1%3s", "L");
    // s21_sprintf(str2, "1%-5s2", "!L");
    // s21_sprintf(str2, "a, %f, c", 3.001);
    // s21_sprintf(str2, "a, %+f, c", 3.001);
    // s21_sprintf(str2, "_%d", 123);
    // s21_sprintf(str2, "_%ld_", 123456789L);

    // s21_strchr
    // s21_strcspn
    // s21_strerror
    // s21_strlen
    // s21_strncat
    // s21_strncmp
    // s21_strncpy
    // s21_strpbrk
    // s21_strrchr
    // s21_strstr
    // s21_strtok
    free(result);
    // s21_trim
    // s21_to_upper
    // s21_to_lower

    return 0;
}