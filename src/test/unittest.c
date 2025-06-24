#include <check.h>
#include <string.h>

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
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_string");

  tc_core = tcase_create("Core");
  // ================================ BASETYPES ============================
  tcase_add_test(tc_core, test_s21_null);
  tcase_add_test(tc_core, test_s21_size_t);
  // ================================ STR_LEN ==============================
  tcase_add_test(tc_core, test_strlen_empty);
  tcase_add_test(tc_core, test_strlen_single_char);
  tcase_add_test(tc_core, test_strlen_hundredsixty);
  // ================================ STR_N_CMP ============================
  tcase_add_test(tc_core, test_strncmp_empty);
  tcase_add_test(tc_core, test_strncmp_single_char);
  tcase_add_test(tc_core, test_strncmp_different);
  // ================================ STR_MEM_CHR ==========================
  tcase_add_test(tc_core, test_memchr_instr);
  tcase_add_test(tc_core, test_memchr_nochrinstr);
  tcase_add_test(tc_core, test_memchr_nol);
  tcase_add_test(tc_core, test_memchr_bin);
  // ================================ STR_N_CPY ============================
  tcase_add_test(tc_core, test_str_n_copy_full);
  tcase_add_test(tc_core, test_str_n_partial_copy);
  tcase_add_test(tc_core, test_str_n_copy_with_zeros);
  tcase_add_test(tc_core, test_str_n_copy_empty_string);
  // ================================ STR CHR ==============================
  tcase_add_test(tc_core, test_strchr_char_fullchar);
  tcase_add_test(tc_core, test_strchr_char_nochar);
  // ================================ MEM SET ==============================
  // ================================ MEM CPY ==============================
  // tcase_add_test(tc_core, test_memcpy_basic);
  // ================================ MEM CMP ==============================
  //tcase_add_test(tc_core, test_memcmp_equal);
  // =======================================================================
  suite_add_tcase(s, tc_core);

  return s;
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