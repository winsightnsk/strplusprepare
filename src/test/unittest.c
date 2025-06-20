#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// ================================ BASETYPES ============================
START_TEST(test_s21_null) {
  ck_assert_ptr_eq(s21_NULL, NULL);  // Проверяем, что s21_NULL == NULL
  int *ptr = s21_NULL;
  ck_assert_ptr_null(ptr);  // Проверяем, что указатель действительно NULL
}
END_TEST
START_TEST(test_s21_size_t) {
  s21_size_t a = 1;
  ck_assert_uint_eq(a, 1ULL);
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
  char *str = malloc(161);
  char *pnt = str;
  for (int i = 160; i >= 0; i--) {
    *pnt = (char)i;
    pnt++;
  }
  ck_assert_uint_eq(s21_strlen(str), strlen(str));
  free(str);
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
  for (size_t i = 0; i < strlen(str2 + 1); i++)
    ck_assert_int_eq(s21_strncmp(str1, str2, i), strncmp(str1, str2, i));
}

// ================================ STR_MEM_CHR ==========================
START_TEST(test_memchr_instr) {
  const char *str = "Hello, world!";
  for (size_t i = 0; i < strlen(str); i++) {
    ck_assert_ptr_eq(s21_memchr(str, (int)str[i], strlen(str)),
                     memchr(str, (int)str[i], strlen(str)));
  }
}
END_TEST
START_TEST(test_memchr_nochrinstr) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_memchr(str, 'z', strlen(str)),
                   memchr(str, 'z', strlen(str)));
  ck_assert_ptr_eq(s21_memchr(str, 'd', 5), memchr(str, 'd', 5));
}
END_TEST
START_TEST(test_memchr_nol) {
  const char *str = "Hello, world!";
  int c = '\0';
  ck_assert_ptr_eq(s21_memchr(str, c, strlen(str) + 1),
                   memchr(str, c, strlen(str) + 1));
}
END_TEST
START_TEST(test_memchr_bin) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  int c = 0x03;
  ck_assert_ptr_eq(s21_memchr(data, c, sizeof(data)),
                   memchr(data, c, sizeof(data)));
}
END_TEST

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