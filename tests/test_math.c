#include <check.h>
#include "../src/math/math.h"

START_TEST(test_add) {
    ck_assert_int_eq(add(2, 3), 5);
    ck_assert_int_eq(add(-1, 1), 0);
    ck_assert_int_eq(add(0, 0), 0);
}
END_TEST

START_TEST(test_subtract) {
    ck_assert_int_eq(subtract(5, 3), 2);
    ck_assert_int_eq(subtract(10, 20), -10);
    ck_assert_int_eq(subtract(0, 0), 0);
}
END_TEST

START_TEST(test_divide_normal) {
    ck_assert_int_eq(divide(10, 2), 5);
    ck_assert_int_eq(divide(9, 3), 3);
}
END_TEST

// START_TEST(test_divide_by_zero) {
//     // Проверяем, что функция завершает программу при делении на ноль
//     ck_assert_exit(divide(10, 0));
// }
// END_TEST

// Обновляем math_suite:
Suite *math_suite(void) {
    Suite *s;
    TCase *tc_core; //, *tc_exit;

    s = suite_create("Math");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_add);
    tcase_add_test(tc_core, test_subtract);
    tcase_add_test(tc_core, test_divide_normal);
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