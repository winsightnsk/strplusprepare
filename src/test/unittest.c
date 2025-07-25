#include <check.h>
#include <limits.h>
// #include <signal.h>  // Добавлено для SIGSEGV
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// Функция для заполнения строки из символов ASCII от 127 до 0
void feelString(char *str) {
  char *pnt = str;
  for (int i = 127; i >= 0; i--) {
    *pnt = (char)i;
    pnt++;
  }
}

// Заполняет count ячеек символом character и добавляет \0
void feelCharString(char *str, char character, s21_size_t count) {
  memset(str, character, count);
  *(str + count) = '\0';
}

// ================================ BASETYPES ============================
START_TEST(test_s21_null) {
  ck_assert_ptr_eq(s21_NULL, NULL);  // Проверяем, что s21_NULL == NULL
  int *ptr = s21_NULL;
  ck_assert_ptr_null(ptr);  // Проверяем, что указатель действительно NULL
}
END_TEST
START_TEST(test_s21_size_t) {
  const s21_size_t a = 1;
  ck_assert_uint_eq(a, 1UL);
}
END_TEST
void testCommon(TCase *tc_core) {
  tcase_add_test(tc_core, test_s21_null);
  tcase_add_test(tc_core, test_s21_size_t);
}

// ================================ STR_LEN ==============================
START_TEST(test_strlen_empty) {
  const char *str = "";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST
START_TEST(test_strlen_single_char) {
  const char *str = "a";
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST
START_TEST(test_strlen_hundredsixty) {
  char str[128];
  feelString(str);
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
}
END_TEST
void testStrLen(TCase *tc_core) {
  tcase_add_test(tc_core, test_strlen_empty);
  tcase_add_test(tc_core, test_strlen_single_char);
  tcase_add_test(tc_core, test_strlen_hundredsixty);
}

// ================================ STR_N_CMP ============================
START_TEST(test_strncmp_empty) {
  const char *str1 = "";
  const char *str2 = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST
START_TEST(test_strncmp_single_char) {
  const char *str1 = "a";
  const char *str2 = "a";
  const char *str3 = "b";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
  ck_assert_int_eq(s21_strncmp(str1, str3, 1), strncmp(str1, str3, 1));
  ck_assert_int_eq(s21_strncmp(str3, str1, 1), strncmp(str3, str1, 1));
}
END_TEST
START_TEST(test_strncmp_different) {
  const char *str1 = "Hello";
  const char *str2 = "Hello, World!";
  for (s21_size_t i = 0; i < s21_strlen(str2 + 1); i++)
    ck_assert_int_eq(s21_strncmp(str1, str2, i), strncmp(str1, str2, i));
}
void testStrNCmp(TCase *tc_core) {
  tcase_add_test(tc_core, test_strncmp_empty);
  tcase_add_test(tc_core, test_strncmp_single_char);
  tcase_add_test(tc_core, test_strncmp_different);
}

// ================================ STR_MEM_CHR ==========================
START_TEST(test_memchr_instr) {
  const char *str = "Hello, world!";
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    ck_assert_ptr_eq(s21_memchr(str, (int)str[i], s21_strlen(str)),
                     memchr(str, (int)str[i], s21_strlen(str)));
  }
}
END_TEST
START_TEST(test_memchr_nochrinstr) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, 'z', s21_strlen(str)),
                   memchr(str, 'z', s21_strlen(str)));
  ck_assert_ptr_eq(s21_memchr(str, 'd', 5), memchr(str, 'd', 5));
}
END_TEST
START_TEST(test_memchr_nol) {
  const char *str = "Hello, world!";
  const int c = '\0';
  ck_assert_ptr_eq(s21_memchr(str, c, s21_strlen(str) + 1),
                   memchr(str, c, s21_strlen(str) + 1));
}
END_TEST
START_TEST(test_memchr_bin) {
  const unsigned char data[] = {200, 100, 0, 150, 8, 185, 160};
  for (unsigned long i = 0; i < sizeof(data); i++) {
    ck_assert_ptr_eq(s21_memchr(data, data[i], sizeof(data)),
                     memchr(data, data[i], sizeof(data)));
  }
}
END_TEST
void testMemChr(TCase *tc_core) {
  tcase_add_test(tc_core, test_memchr_instr);
  tcase_add_test(tc_core, test_memchr_nochrinstr);
  tcase_add_test(tc_core, test_memchr_nol);
  tcase_add_test(tc_core, test_memchr_bin);
}

// ================================ STR_N_CPY ============================
START_TEST(test_str_n_copy_full) {
  char src[128];
  feelString(src);
  char dest[128];
  s21_strncpy(dest, src, s21_strlen(src));
  ck_assert_str_eq(dest, src);
}
END_TEST
START_TEST(test_str_n_partial_copy) {
  const char *src = "Hello, world!";
  char dest[15];
  feelCharString(dest, '_', 14);
  s21_strncpy(dest, src, 5);
  ck_assert_int_eq(s21_strncmp(dest, "Hello", 5), 0);
  // assert_strn_eq(dest, "Hello", 5);
  ck_assert(dest[5] != '\0');  // strncpy не добавляет '\0' при n <= strlen(src)
}
END_TEST
START_TEST(test_str_n_copy_with_zeros) {
  const char *src = "Hello!";
  char dest[15] = {0};
  s21_size_t len = s21_strlen(src);
  s21_strncpy(dest, src, 13);
  ck_assert_int_eq(s21_strncmp(dest, src, len), 0);
  // assert_strn_eq(dest, src, len);
  for (s21_size_t i = len; i < 13; i++) {
    ck_assert(dest[i] == '\0');
  }
}
END_TEST
START_TEST(test_str_n_copy_empty_string) {
  char dest[100] = "Garbage";
  s21_strncpy(dest, "", 10);
  ck_assert(dest[0] == '\0');
}
END_TEST
void testStrNCpy(TCase *tc_core) {
  tcase_add_test(tc_core, test_str_n_copy_full);
  tcase_add_test(tc_core, test_str_n_partial_copy);
  tcase_add_test(tc_core, test_str_n_copy_with_zeros);
  tcase_add_test(tc_core, test_str_n_copy_empty_string);
}

// ================================ STR CHR ==============================
START_TEST(test_strchr_char_fullchar) {
  char str[128];
  feelString(str);
  char *result = NULL;
  char *expected = NULL;
  for (s21_size_t i = 0; i < 128; i++) {
    result = s21_strchr(str, str[i]);
    expected = strchr(str, str[i]);
    ck_assert_ptr_eq(result, expected);
  }
}
END_TEST
START_TEST(test_strchr_char_nochar) {
  const char *str = "Hello, World!";
  char *result = NULL;
  char *expected = NULL;
  char seekch[128];
  feelString(seekch);
  for (s21_size_t i = 0; i < 127; i++) {
    result = s21_strchr(str, seekch[i]);
    expected = strchr(str, seekch[i]);
    ck_assert_ptr_eq(result, expected);
  }
}
END_TEST
START_TEST(test_strchr_empty_string) {
  const char *str = "";
  char seekch[128];
  feelString(seekch);
  char *result = NULL;
  char *expected = NULL;
  for (s21_size_t i = 0; i < 128; i++) {
    result = s21_strchr(str, seekch[i]);
    expected = strchr(str, seekch[i]);
    ck_assert_ptr_eq(result, expected);
  }
}
END_TEST
START_TEST(test_strchr_first_occurrence) {
  const char *str = "Hello, World!";
  // Должен вернуть указатель на первую 'l'
  char *result = s21_strchr(str, 'l');
  char *expected = strchr(str, 'l');
  ck_assert_ptr_eq(result, expected);
}
END_TEST
void testStrChr(TCase *tc_core) {
  tcase_add_test(tc_core, test_strchr_char_fullchar);
  tcase_add_test(tc_core, test_strchr_char_nochar);
  tcase_add_test(tc_core, test_strchr_empty_string);
  tcase_add_test(tc_core, test_strchr_first_occurrence);
}

// ================================ STR N CAT ============================
START_TEST(test_strncat_basic) {
  char str[14] = "Hello";
  const char *postfix = ", World!";
  char *ptr = s21_strncat(str, postfix, 8);
  ck_assert_str_eq(str, "Hello, World!");
  ck_assert_ptr_eq(str, ptr);
}
END_TEST
START_TEST(test_strncat_with_limit) {
  char dest[13] = "Hello";
  const char *src = ", World!";
  s21_strncat(dest, src, 3);
  ck_assert_str_eq(dest, "Hello, W");
}
END_TEST
START_TEST(test_strncat_empty_src) {
  char dest_base[14] = "Hello";
  char dest_s21[14] = "Hello";
  const char *src = "";
  size_t n = 5;
  strncat(dest_base, src, n);
  s21_strncat(dest_s21, src, n);
  ck_assert_str_eq(dest_base, dest_s21);
}
END_TEST
START_TEST(test_strncat_zero_n) {
  char dest_base[14] = "Hello";
  char dest_s21[14] = "Hello";
  const char *src = ", World!";
  size_t n = 0;
  strncat(dest_base, src, n);
  s21_strncat(dest_s21, src, n);
  ck_assert_str_eq(dest_base, dest_s21);
}
END_TEST
START_TEST(test_strncat_n_greater_than_src) {
  char dest_base[14] = "Hello";
  char dest_s21[14] = "Hello";
  const char *src = "!";
  size_t n = 5;
  strncat(dest_base, src, n);
  s21_strncat(dest_s21, src, n);
  ck_assert_str_eq(dest_base, dest_s21);
}
END_TEST
void testStrNCat(TCase *tc_core) {  //, TCase *tc_limits) {
  tcase_add_test(tc_core, test_strncat_basic);
  tcase_add_test(tc_core, test_strncat_with_limit);
  tcase_add_test(tc_core, test_strncat_empty_src);
  tcase_add_test(tc_core, test_strncat_zero_n);
  tcase_add_test(tc_core, test_strncat_n_greater_than_src);
  // tcase_add_test_raise_signal(tc_limits, test_strncat_null_dest, SIGSEGV);
}

// ================================ STR PBRK ============================
START_TEST(test_s21_strpbrk_basic) {
  const char *str = "Hello, world!";
  const char *accept = " ,!";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_no_match) {
  const char *str = "Hello";
  const char *accept = "123";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_empty_accept) {
  const char *str = "Hello";
  const char *accept = "";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_empty_str) {
  const char *str = "";
  const char *accept = "abc";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_first_char_match) {
  const char *str = "abcde";
  const char *accept = "a";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_last_char_match) {
  const char *str = "abcdef";
  const char *accept = "f";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_multiple_matches) {
  const char *str = "This is a test";
  const char *accept = "aeiou";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_null_terminator_in_accept) {
  const char *str = "Hello\0world";
  const char *accept = "\0";
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_s21_strpbrk_full_string) {
  char str[128];
  feelString(str);
  char accept[26];
  for (int i = 1; i <= 25; i++) {
    accept[i - 1] = i * 5;
  }
  accept[25] = '\0';
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
void testStrPbrk(TCase *tc_core) {
  tcase_add_test(tc_core, test_s21_strpbrk_basic);
  tcase_add_test(tc_core, test_s21_strpbrk_no_match);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_accept);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_str);
  tcase_add_test(tc_core, test_s21_strpbrk_first_char_match);
  tcase_add_test(tc_core, test_s21_strpbrk_last_char_match);
  tcase_add_test(tc_core, test_s21_strpbrk_multiple_matches);
  tcase_add_test(tc_core, test_s21_strpbrk_null_terminator_in_accept);
  tcase_add_test(tc_core, test_s21_strpbrk_full_string);
}

// ================================ STR CSPN =============================
START_TEST(test_cspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_empty_str2) {
  const char *str1 = "hello";
  const char *str2 = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_both_empty) {
  const char *str1 = "";
  const char *str2 = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_no_matches) {
  const char *str1 = "hello world";
  const char *str2 = "xyz";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_first_char_match) {
  const char *str1 = "apple";
  const char *str2 = "a";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_last_char_match) {
  const char *str1 = "banana";
  const char *str2 = "a";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_multiple_matches) {
  const char *str1 = "programming";
  const char *str2 = "gm";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_all_chars_match) {
  const char *str1 = "aaa";
  const char *str2 = "a";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_cspn_special_chars) {
  const char *str1 = "hello\nworld\t!";
  const char *str2 = "\t\n";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
START_TEST(test_long_strings) {
  char str1[128];
  feelString(str1);
  const char *str2 = "xyzq";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST
void testStrCspn(TCase *tc_core) {
  tcase_add_test(tc_core, test_cspn_empty_str1);
  tcase_add_test(tc_core, test_cspn_empty_str2);
  tcase_add_test(tc_core, test_cspn_both_empty);
  tcase_add_test(tc_core, test_cspn_no_matches);
  tcase_add_test(tc_core, test_cspn_first_char_match);
  tcase_add_test(tc_core, test_cspn_last_char_match);
  tcase_add_test(tc_core, test_cspn_multiple_matches);
  tcase_add_test(tc_core, test_cspn_all_chars_match);
  tcase_add_test(tc_core, test_cspn_special_chars);
  tcase_add_test(tc_core, test_long_strings);
}

// ================================ MEM CPY ==============================
START_TEST(test_memcpy_basic) {
  char src[128];
  feelString(src);
  char result[128];
  char expected[128];
  memset(result, '_', 128);
  memset(expected, '_', 128);
  s21_memcpy(result, src, 128);
  memcpy(expected, src, 128);
  ck_assert_str_eq(result, expected);
  // assert_strn_eq(result, expected, 128);
}
END_TEST
START_TEST(test_memcpy_partial) {
  const char src[] = "Testing partial copy";
  char expected[20] = {0};
  char result[20] = {0};
  s21_size_t len = 7;  // Копируем только "Testing"
  memcpy(expected, src, len);
  s21_memcpy(result, src, len);
  ck_assert_int_eq(memcmp(expected, result, len), 0);
}
END_TEST
START_TEST(test_memcpy_zero_bytes) {
  const char src[] = "Should not copy anything";
  char expected[9] = "Original";
  char result[9] = "Original";
  memcpy(expected, src, 0);
  s21_memcpy(result, src, 0);
  ck_assert_int_eq(memcmp(expected, result, 9), 0);
}
END_TEST
// START_TEST(test_memcpy_overlap) {
//   char buffer1[14] = "Hello, world!";
//   char buffer2[14] = "Hello, world!";
//   memcpy(buffer1 + 5, buffer1, 7);
//   s21_memcpy(buffer2 + 5, buffer2, 7);
//   ck_assert_int_eq(memcmp(buffer1, buffer2, 14), 0);
// }
END_TEST
START_TEST(test_memcpy_non_string_data) {
  int src[] = {1, 2, 3, 4, 5};
  int expected[5] = {0};
  int result[5] = {0};
  s21_size_t len = sizeof(src);
  memcpy(expected, src, len);
  s21_memcpy(result, src, len);
  ck_assert_int_eq(memcmp(expected, result, len), 0);
}
void testMemCpy(TCase *tc_core) {
  tcase_add_test(tc_core, test_memcpy_basic);
  tcase_add_test(tc_core, test_memcpy_partial);
  tcase_add_test(tc_core, test_memcpy_zero_bytes);
  // tcase_add_test(tc_core, test_memcpy_overlap);
  tcase_add_test(tc_core, test_memcpy_non_string_data);
}

// ================================ MEM SET ==============================
START_TEST(test_memset_darkside) {
  char pCharR[25];
  char pCharE[25];
  unsigned char pUCharR[25];
  unsigned char pUCharE[25];
  short pShortE[25];
  short pShortR[25];
  unsigned short pUShortE[25];
  unsigned short pUShortR[25];
  int pIntE[25];
  int pIntR[25];
  unsigned int pUIntE[25];
  unsigned int pUIntR[25];
  // Значения 2-байтовых и 4-байтовых элементов будут отличны от единицы
  for (int value = -1; value < UCHAR_MAX; value += 1) {
    memset(pCharE, value, sizeof(pCharE));  // 1
    s21_memset(pCharR, value, sizeof(pCharR));
    ck_assert_mem_eq(pCharE, pCharR, sizeof(pCharE));
    memset(pUCharE, value, sizeof(pUCharE));  // 1
    s21_memset(pUCharR, value, sizeof(pUCharR));
    ck_assert_mem_eq(pUCharE, pUCharR, sizeof(pUCharE));
    memset(pShortE, value, sizeof(pShortE));  // 257
    s21_memset(pShortR, value, sizeof(pShortR));
    ck_assert_mem_eq(pShortE, pShortR, sizeof(pShortE));
    memset(pUShortE, value, sizeof(pUShortE));  // 257
    s21_memset(pUShortR, value, sizeof(pUShortR));
    ck_assert_mem_eq(pUShortE, pUShortR, sizeof(pUShortE));
    memset(pIntE, value, sizeof(pIntE));  // 16843009
    s21_memset(pIntR, value, sizeof(pIntR));
    ck_assert_mem_eq(pIntE, pIntR, sizeof(pIntE));
    memset(pUIntE, value, sizeof(pUIntE));  // 16843009
    s21_memset(pUIntR, value, sizeof(pUIntR));
    ck_assert_mem_eq(pUIntE, pUIntR, sizeof(pUIntE));
  }
}
START_TEST(test_memset_basic) {
  char result[10];
  char expected[10];
  s21_memset(result, 0, 10);
  memset(expected, 0, 10);
  ck_assert_mem_eq(result, expected, 10);
  s21_memset(result, 'A', 5);
  memset(expected, 'A', 5);
  ck_assert_mem_eq(result, expected, 10);
}
END_TEST
START_TEST(test_memset_edge_cases) {
  char buffer[10] = "123456789";
  s21_memset(buffer, 'X', 0);
  ck_assert_str_eq(buffer, "123456789");
  s21_memset(buffer, 'Y', 1);
  ck_assert_str_eq(buffer, "Y23456789");
}
void testMemSet(TCase *tc_core) {
  tcase_add_test(tc_core, test_memset_darkside);
  tcase_add_test(tc_core, test_memset_basic);
  tcase_add_test(tc_core, test_memset_edge_cases);
}

// ================================ MEM CMP ==============================
START_TEST(test_memcmp_equal) {
  char str1[128];
  feelString(str1);
  char str2[128];
  feelString(str2);
  s21_size_t n = s21_strlen(str1);
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_memcmp_different) {
  const char str1[] = "Hello, world!";
  const char str2[] = "Hello, World!";
  s21_size_t n = s21_strlen(str1);

  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);

  ck_assert_int_eq(result > 0, expected > 0);
  ck_assert(result != 0);
}
END_TEST
START_TEST(test_memcmp_partial) {
  const char str1[] = "Hello, world!";
  const char str2[] = "Hello, there!";
  s21_size_t n = 7;  // Сравниваем только "Hello, "
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_memcmp_zero_length) {
  const char str1[] = "Hello, world!";
  const char str2[] = "Goodbye, world!";
  s21_size_t n = 0;  // Нулевая длина
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(test_memcmp_binary_data) {
  const unsigned char data1[] = {0x00, 0x01, 0x02, 0x03, 0xFF};
  const unsigned char data2[] = {0x00, 0x01, 0x02, 0x04, 0xFE};
  s21_size_t n = sizeof(data1);
  int result = s21_memcmp(data1, data2, n);
  int expected = memcmp(data1, data2, n);
  ck_assert_int_eq(result, expected);
  ck_assert(result < 0);  // 0x03 < 0x04
}
END_TEST
START_TEST(test_memcmp_one_byte_diff) {
  const char str1[] = "abcde";
  const char str2[] = "abcdf";
  s21_size_t n = strlen(str1);
  int result = s21_memcmp(str1, str2, n);
  int expected = memcmp(str1, str2, n);
  ck_assert_int_eq(result, expected);
  ck_assert(result < 0);  // 'e' < 'f'
}
END_TEST
void testMemCmp(TCase *tc_core) {
  tcase_add_test(tc_core, test_memcmp_equal);
  tcase_add_test(tc_core, test_memcmp_different);
  tcase_add_test(tc_core, test_memcmp_partial);
  tcase_add_test(tc_core, test_memcmp_zero_length);
  tcase_add_test(tc_core, test_memcmp_binary_data);
  tcase_add_test(tc_core, test_memcmp_one_byte_diff);
}

// ================================ STR STR ==============================
START_TEST(test_strstr_exists) {
  const char *str = "Hello, world!";
  const char *substr = "world";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_empty_needle) {
  const char *str = "Hello, world!";
  const char *substr = "";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_empty_haystack) {
  const char *str = "";
  const char *substr = "world";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_both_empty) {
  const char *str = "";
  const char *substr = "";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_equals) {
  const char *str = "Hello, world!";
  const char *substr = "Hello, world!";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_needle_longer) {
  const char *str = "Hello";
  const char *substr = "Hello, world!";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_multiple_occurrences) {
  const char *str = "Hello, hello, HELLO, hello!";
  const char *substr = "hello";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST
START_TEST(test_strstr_fullchars) {
  char str[128];
  feelString(str);
  char substr[2] = {0};
  for (int i = 0; i < 128; i++) {
    substr[0] = i;
    ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
  }
}
END_TEST
void testStrStr(TCase *tc_core) {
  tcase_add_test(tc_core, test_strstr_exists);
  tcase_add_test(tc_core, test_strstr_empty_needle);
  tcase_add_test(tc_core, test_strstr_empty_haystack);
  tcase_add_test(tc_core, test_strstr_both_empty);
  tcase_add_test(tc_core, test_strstr_equals);
  tcase_add_test(tc_core, test_strstr_needle_longer);
  tcase_add_test(tc_core, test_strstr_multiple_occurrences);
  tcase_add_test(tc_core, test_strstr_fullchars);
}

// ================================ STR R CHR =============================
START_TEST(test_strrchr_fullchars) {
  char str[128];
  feelString(str);
  for (int i = 0; i < 128; i++)
    ck_assert_ptr_eq(s21_strrchr(str, i), strrchr(str, i));
}
END_TEST
START_TEST(test_strrchr_noCharsIn) {
  const char *str = "[128]";
  for (int i = 0; i < 128; i++)
    ck_assert_ptr_eq(s21_strrchr(str, i), strrchr(str, i));
}
END_TEST
START_TEST(test_strrchr_DoubleChars) {
  char str[255];
  feelString(str);
  feelString(str + 127);
  for (int i = 0; i < 128; i++)
    ck_assert_ptr_eq(s21_strrchr(str, i), strrchr(str, i));
}
END_TEST
START_TEST(test_strrchr_empty_string) {
  const char *str = "";
  char *result = s21_strrchr(str, 'a');
  char *expected = strrchr(str, 'a');
  ck_assert_ptr_eq(result, expected);
  result = s21_strrchr(str, '\0');
  expected = strrchr(str, '\0');
  ck_assert_ptr_eq(result, expected);
}
END_TEST
START_TEST(test_strrchr_repeated_chars) {
  const char *str = "aaabbbaaacccaaa";
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
  ck_assert_ptr_eq(s21_strrchr(str, 'b'), strrchr(str, 'b'));
}
END_TEST
void testStrRChr(TCase *tc_core) {
  tcase_add_test(tc_core, test_strrchr_fullchars);
  tcase_add_test(tc_core, test_strrchr_noCharsIn);
  tcase_add_test(tc_core, test_strrchr_DoubleChars);
  tcase_add_test(tc_core, test_strrchr_empty_string);
  tcase_add_test(tc_core, test_strrchr_repeated_chars);
}

// ================================ STR TOK =============================
int compareStrTok(const char *str, const char *delim) {
  int result = 1;
  s21_size_t cnt = s21_strlen(str) + 1;
  char *s21clone = malloc(cnt);
  char *libclone = malloc(cnt);
  strcpy(s21clone, str);
  strcpy(libclone, str);

  const char *s21_ptr = s21_strtok(s21clone, delim);
  const char *lib_ptr = strtok(libclone, delim);
  while (result && s21_ptr && lib_ptr) {
    if (strcmp(s21_ptr, lib_ptr) != 0) {
      result = 0;
    } else {
      s21_ptr = s21_strtok(NULL, delim);
      lib_ptr = strtok(NULL, delim);
    }
  }
  if (s21_ptr != lib_ptr) result = 0;
  if (s21_memcmp(s21clone, libclone, cnt) != 0) result = 0;

  free(s21clone);
  free(libclone);
  return result;
}
START_TEST(test_strtok_simple) {
  ck_assert_int_eq(compareStrTok("aaa bbb", " "), 1);
  ck_assert_int_eq(compareStrTok(" aaa bbb", " "), 1);
  ck_assert_int_eq(compareStrTok("aaa bbb ", " "), 1);
  ck_assert_int_eq(compareStrTok("aaabbb", " "), 1);
  ck_assert_int_eq(compareStrTok("   a b bb", " "), 1);
  ck_assert_int_eq(compareStrTok("aaa bbb   ", " "), 1);
}
END_TEST
START_TEST(test_strtok_bigstring) {
  char str[128];
  feelString(str);
  char delim[20] = {0};
  for (int i = 0; i < 20; i++) delim[i] = (i + 1) * 5;
  ck_assert_int_eq(compareStrTok(str, delim), 1);
}
END_TEST
START_TEST(test_strtok_multiple_delimiters) {
  const char *str = "Hello world\tthis\nis\ra\ftest";
  ck_assert_int_eq(compareStrTok(str, " \t\n\r\f"), 1);
}
END_TEST
START_TEST(test_strtok_only_delimiters) {
  ck_assert_int_eq(compareStrTok(",,,,,", ","), 1);
}
END_TEST
START_TEST(test_strtok_empty_string) {
  ck_assert_int_eq(compareStrTok("", ","), 1);
}
END_TEST
void testStrTok(TCase *tc_core) {
  tcase_add_test(tc_core, test_strtok_simple);
  tcase_add_test(tc_core, test_strtok_bigstring);
  tcase_add_test(tc_core, test_strtok_multiple_delimiters);
  tcase_add_test(tc_core, test_strtok_only_delimiters);
  tcase_add_test(tc_core, test_strtok_empty_string);
}
// ================================ STR ERROR=============================
START_TEST(test_strerror) {
  for (int i = -1; i <= 255; i++) {
    char *result = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(result, expected);
  }
}
END_TEST
void testStrError(TCase *tc_core) { tcase_add_test(tc_core, test_strerror); }
// ================================ -+- sprintf -+- ======================
START_TEST(test_sprintf_spec_c) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "a, %c, c", 'b');
  int expNum = sprintf(expString, "a, %c, c", 'b');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%c,%c", '_', '_');
  expNum = sprintf(expString, "%c,%c", '_', '_');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "!");
  expNum = sprintf(expString, "!");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%c", '\0');
  expNum = sprintf(expString, "%c", '\0');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%c_", '\0');
  expNum = sprintf(expString, "_%c_", '\0');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_c_width) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "%3c", '!');
  int expNum = sprintf(expString, "%3c", '!');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%23c", '!');
  expNum = sprintf(expString, "%23c", '!');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_c_alignleft) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "%-3c", '!');
  int expNum = sprintf(expString, "%-3c", '!');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%-23c", '!');
  expNum = sprintf(expString, "%-23c", '!');
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_s) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "a, %s, c", "bBb");
  int expNum = sprintf(expString, "a, %s, c", "bBb");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%s", "aBc");
  expNum = sprintf(expString, "%s", "aBc");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%s%s", "aBc", "d");
  expNum = sprintf(expString, "%s%s", "aBc", "d");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "1%s2", "");
  expNum = sprintf(expString, "1%s2", "");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_s_width) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "1%5s2", "!L");
  int expNum = sprintf(expString, "1%5s2", "!L");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "1%15s2", "?");
  expNum = sprintf(expString, "1%15s2", "?");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "1%3s2", "!!!!!!!!!!!!!!!!!!!!");
  expNum = sprintf(expString, "1%3s2", "!!!!!!!!!!!!!!!!!!!!");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_s_alignleft) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "1%-5s2", "!L");
  int expNum = sprintf(expString, "1%-5s2", "!L");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "1%-15s2", "?");
  expNum = sprintf(expString, "1%-15s2", "?");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "1%-3s2", "!!!!!!!!!!!!!!!!!!!!");
  expNum = sprintf(expString, "1%-3s2", "!!!!!!!!!!!!!!!!!!!!");
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_f) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "a, %f, c", 3.001);
  int expNum = sprintf(expString, "a, %f, c", 3.001);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%f,%f", 0.00, -2.25);
  expNum = sprintf(expString, "%f,%f", 0.00, -2.25);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%f", 101.101);
  expNum = sprintf(expString, "%f", 101.101);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%f", -1.00001);
  expNum = sprintf(expString, "%f", -1.00001);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%15f", -110.01);
  expNum = sprintf(expString, "%15f", -110.01);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%4f", -110.01);
  expNum = sprintf(expString, "%4f", -110.01);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "%f", 1.999);
  expNum = sprintf(expString, "%f", 1.999);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_f_space_plus) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "a, %+f, c", 3.001);
  int expNum = sprintf(expString, "a, %+f, c", 3.001);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_% f_", 2.25);
  expNum = sprintf(expString, "_% f_", 2.25);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%+16f_", 2.25);
  expNum = sprintf(expString, "_%+16f_", 2.25);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%+16f% 16f_", 1.23, 4.5);
  expNum = sprintf(expString, "_%+16f% 16f_", 1.23, 4.5);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%-+16f_", 1.23);
  expNum = sprintf(expString, "_%-+16f_", 1.23);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_set_specs_basic) {
  const char *format = "+- 10.5l";
  s21_size_t ptr = 0;
  Spec specs = {0};
  set_specs(&specs, format, &ptr);
  ck_assert_int_eq(specs.plus, 1);
  ck_assert_int_eq(specs.minus, 1);
  ck_assert_int_eq(specs.space, 0);  // так как space=1 только если не plus
  ck_assert_int_eq(specs.width, 10);
  ck_assert_int_eq(specs.accuracy, 5);
  ck_assert_int_eq(specs.lenght, 1);  // так как 'l' в конце
  // Проверка положения указателя после вызова
  ck_assert_int_eq(ptr, strlen(format));
}
END_TEST
START_TEST(test_sprintf_spec_d_d) {
  char resString[128];
  char expString[128];
  int resNum = s21_sprintf(resString, "_%d", 123);
  int expNum = sprintf(expString, "_%d", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5d_", 123);
  expNum = sprintf(expString, "_%5d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5.0d_", 123);
  expNum = sprintf(expString, "_%5.0d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5.9d_", 123);
  expNum = sprintf(expString, "_%5.9d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5.9d_", -123);
  expNum = sprintf(expString, "_%5.9d_", -123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%+5d_", 123);
  expNum = sprintf(expString, "_%+5d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%+-5d_", 123);
  expNum = sprintf(expString, "_%+-5d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%+5d_", -123);
  expNum = sprintf(expString, "_%+5d_", -123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_% 5d_", 123);
  expNum = sprintf(expString, "_% 5d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%-5d_", -123);
  expNum = sprintf(expString, "_%-5d_", -123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%-5d_", 123);
  expNum = sprintf(expString, "_%-5d_", 123);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST
START_TEST(test_sprintf_spec_d_ld_hd_0) {
  char resString[128];
  char expString[128];
  short a = 1;
  int resNum = s21_sprintf(resString, "_%ld_", 123456789L);
  int expNum = sprintf(expString, "_%ld_", 123456789L);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%15ld_", 123456789L);
  expNum = sprintf(expString, "_%15ld_", 123456789L);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%hd_", a);
  expNum = sprintf(expString, "_%hd_", a);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5hd_", a);
  expNum = sprintf(expString, "_%5hd_", a);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%d_", 0);
  expNum = sprintf(expString, "_%d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_% d_", 0);
  expNum = sprintf(expString, "_% d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5d_", 0);
  expNum = sprintf(expString, "_%5d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%-5d_", 0);
  expNum = sprintf(expString, "_%-5d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5.0d_", 0);
  expNum = sprintf(expString, "_%5.0d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%5.9d_", 0);
  expNum = sprintf(expString, "_%5.9d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
  resNum = s21_sprintf(resString, "_%.0d_", 0);
  expNum = sprintf(expString, "_%.0d_", 0);
  ck_assert_int_eq(resNum, expNum);
  ck_assert_str_eq(resString, expString);
}
END_TEST

void testSprintf(TCase *tc_core) {
  tcase_add_test(tc_core, test_sprintf_spec_c);
  tcase_add_test(tc_core, test_sprintf_spec_c_width);
  tcase_add_test(tc_core, test_sprintf_spec_c_alignleft);
  tcase_add_test(tc_core, test_sprintf_spec_s);
  tcase_add_test(tc_core, test_sprintf_spec_s_width);
  tcase_add_test(tc_core, test_sprintf_spec_s_alignleft);
  tcase_add_test(tc_core, test_sprintf_spec_f);
  tcase_add_test(tc_core, test_sprintf_spec_f_space_plus);
  tcase_add_test(tc_core, test_set_specs_basic);
  tcase_add_test(tc_core, test_sprintf_spec_d_d);
  tcase_add_test(tc_core, test_sprintf_spec_d_ld_hd_0);
}

// ================================ -+- trim -+- =====================
START_TEST(test_trim_basic) {
  char *result = s21_trim("---abc---xyz----", "-");
  ck_assert_str_eq(result, "abc---xyz");
  free(result);
  result = s21_trim("111111", "1");
  ck_assert_str_eq(result, "");
  free(result);
  result = s21_trim("", "It's gone");
  ck_assert_str_eq(result, "");
  free(result);
  result = s21_trim("I'm going home", "I");
  ck_assert_str_eq(result, "'m going home");
  free(result);
}
END_TEST
void testTrim(TCase *tc_core) { tcase_add_test(tc_core, test_trim_basic); }

// ================================ -+- insert -+- =====================
START_TEST(test_insert_basic) {
  char *result = s21_insert("aaabbb", " ", 3);
  ck_assert_str_eq(result, "aaa bbb");
  free(result);
  result = s21_insert("I'm going home", "slowly ", 4);
  ck_assert_str_eq(result, "I'm slowly going home");
  free(result);
  result = s21_insert(" ", "It's gone", 0);
  ck_assert_str_eq(result, "It's gone ");
  free(result);
  result = s21_insert("hello", "world", 5);
  ck_assert_str_eq(result, "helloworld");
  free(result);
  result = s21_insert("", "It's gone", 0);
  ck_assert_str_eq(result, "It's gone");
  free(result);
  result = s21_insert("It's gone", "", 5);
  ck_assert_str_eq(result, "It's gone");
  free(result);
}
END_TEST
void testInsert(TCase *tc_core) { tcase_add_test(tc_core, test_insert_basic); }

// ================================ -+- to_upper -+- =====================
START_TEST(test_to_upper_basic) {
  char *result = s21_to_upper("123abc_!ABC-z?");
  ck_assert_str_eq(result, "123ABC_!ABC-Z?");
  free(result);
  result = s21_to_upper("");
  ck_assert_str_eq(result, "");
  free(result);
  result = s21_to_upper("\t\n");
  ck_assert_str_eq(result, "\t\n");
  free(result);
}
END_TEST
void testToUpper(TCase *tc_core) {
  tcase_add_test(tc_core, test_to_upper_basic);
}

// ================================ -+- to_lower -+- =====================
START_TEST(test_to_lower_basic) {
  char *result = s21_to_lower("123abc_!ABC-z?");
  ck_assert_str_eq(result, "123abc_!abc-z?");
  free(result);
  result = s21_to_lower("");
  ck_assert_str_eq(result, "");
  free(result);
  result = s21_to_lower("\t\n");
  ck_assert_str_eq(result, "\t\n");
  free(result);
}
END_TEST
void testToLower(TCase *tc_core) {
  tcase_add_test(tc_core, test_to_lower_basic);
}

// =======================================================================

Suite *math_suite(void) {
  Suite *testsuite = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");
  // TCase *tc_limits = tcase_create("Limits");

  testCommon(tc_core);
  testMemChr(tc_core);
  testMemCmp(tc_core);
  testMemCpy(tc_core);
  testMemSet(tc_core);
  testStrChr(tc_core);
  testStrCspn(tc_core);
  testStrLen(tc_core);
  testStrNCat(tc_core);  // , tc_limits);
  testStrNCmp(tc_core);
  testStrNCpy(tc_core);
  testStrPbrk(tc_core);
  testStrStr(tc_core);
  testStrRChr(tc_core);
  testStrTok(tc_core);
  testStrError(tc_core);
  testSprintf(tc_core);
  testTrim(tc_core);
  testInsert(tc_core);
  testToUpper(tc_core);
  testToLower(tc_core);

  suite_add_tcase(testsuite, tc_core);
  // suite_add_tcase(testsuite, tc_limits);

  return testsuite;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = math_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}