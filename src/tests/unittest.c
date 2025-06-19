#include <check.h>

#include "../common/basetypes.h"

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

// START_TEST(test_divide_by_zero) {
//     // Проверяем, что функция завершает программу при делении на ноль
//     ck_assert_exit(divide(10, 0));
// }
// END_TEST

Suite *math_suite(void) {
  Suite *s;
  TCase *tc_core;  //, *tc_exit;

  s = suite_create("Math");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_null);
  tcase_add_test(tc_core, test_s21_size_t);
  suite_add_tcase(s, tc_core);

  /* Exit test case */
  // tc_exit = tcase_create("Exit");
  // tcase_add_test(tc_exit, test_divide_by_zero);
  // suite_add_tcase(s, tc_exit);

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