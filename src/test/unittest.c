#include <check.h>

#include "../s21_string.h"

// ================================ BASETYPES ==============================
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

Suite *math_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_string");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_null);
  tcase_add_test(tc_core, test_s21_size_t);
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