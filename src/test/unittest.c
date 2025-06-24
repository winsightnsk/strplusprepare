#include <check.h>
#include <string.h>

#include <signal.h>  // Добавлено для SIGSEGV
#include "../s21_string.h"

// Свой асерт для проверки частичного раверства строк
void assert_strn_eq(char *dest, char *src, s21_size_t count) {
  for (s21_size_t i = 0; i < count; i++, dest++, src++)
  ck_assert_int_eq(*dest, *src);
}

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
void testBaseTypes(TCase *tc_core) {
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
  // free(str);
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
  assert_strn_eq(dest, "Hello", 5);
  ck_assert(dest[5] != '\0');  // strncpy не добавляет '\0' при n <= strlen(src)
}
END_TEST
START_TEST(test_str_n_copy_with_zeros) {
  char *src = "Hello!";
  char dest[15] = {0};
  s21_size_t len = s21_strlen(src);
  s21_strncpy(dest, src, 13);
  assert_strn_eq(dest, src, len);
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
START_TEST(test_strncat_null_dest) {
  char *dest = NULL;
  const char *src = "test";
  // Ожидаем падение (как и стандартная strncat)
  s21_strncat(dest, src, 3);
}
END_TEST
void testStrNCat(TCase *tc_core, TCase *tc_limits) {
  tcase_add_test(tc_core, test_strncat_basic);
  tcase_add_test(tc_core, test_strncat_with_limit);
  tcase_add_test(tc_core, test_strncat_empty_src);
  tcase_add_test(tc_core, test_strncat_zero_n);
  tcase_add_test(tc_core, test_strncat_n_greater_than_src);
  tcase_add_test_raise_signal(tc_limits, test_strncat_null_dest, SIGSEGV);
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
    accept[i-1] = i * 5;
  }
  accept[25] = '\0';
  char *result = s21_strpbrk(str, accept);
  char *expected = strpbrk(str, accept);
  ck_assert_ptr_eq(result, expected);
}
void  testStrPbrk(TCase *tc_core) {
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
// void testStrCspn(TCase *tc_core) {

// }

// ================================ MEM SET ==============================
// ================================ MEM CPY ==============================
// START_TEST(test_memcpy_basic) {
//     char src[128];
//     feelString(src);
//     char dest0[128];
//     feelCharString(dest0, '_', 128);
//     char dest21[128];
//     feelCharString(dest21, '_', 128);
//     memcpy(dest0, src, 128);
//     s21_memcpy(dest21, src, 128);
//     assert_strn_eq(dest0, dest21, 128);
// }
// END_TEST
// ================================ MEM CMP ==============================
// START_TEST(test_memcmp_equal) {
//     char str1[128];
//     feelString(str1);
//     char str2[128];
//     feelString(str2);
//     s21_size_t n = s21_strlen(str1);
//     int result = s21_memcmp(str1, str2, n);
//     int expected = memcmp(str1, str2, n);
//     ck_assert_int_eq(result, expected);
//     ck_assert_int_eq(result, 0);
// }
// END_TEST
// =======================================================================

Suite *math_suite(void) {
  Suite *testsuite = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");
  TCase *tc_limits = tcase_create("Limits");

  testBaseTypes(tc_core);
  testStrLen(tc_core);
  testStrNCmp(tc_core);
  testMemChr(tc_core);
  testStrNCpy(tc_core);
  testStrChr(tc_core);
  testStrNCat(tc_core, tc_limits);
  testStrPbrk(tc_core);
  // testStrCspn(tc_core);
  // ================================ MEM SET ==============================
  // ================================ MEM CPY ==============================
  // tcase_add_test(tc_core, test_memcpy_basic);
  // ================================ MEM CMP ==============================
  // tcase_add_test(tc_core, test_memcmp_equal);
  // =======================================================================
  suite_add_tcase(testsuite, tc_core);
  suite_add_tcase(testsuite, tc_limits);

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