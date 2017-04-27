#include <check.h>

#include "../src/bloom.h"

START_TEST(check_is_installed_and_testing_code) {
    int expected = 1;
    int actual = foo();

    ck_assert_int_eq(actual, expected);
} END_TEST

int main() {
    Suite *s = suite_create("Bloom Filter");
    TCase *tc = tcase_create("Bloom Filter");
    SRunner *sr = srunner_create(s);

    int num_fails;

    suite_add_tcase(s, tc);

    tcase_add_test(tc, check_is_installed_and_testing_code);

    srunner_run_all(sr, CK_NORMAL);
    num_fails = srunner_ntests_failed(sr);
    srunner_free(sr);

    return num_fails == 0 ? 0 : 1;
}
