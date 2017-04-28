#include <check.h>

#include "../src/bit_field.h"

START_TEST(bit_field_set_bit_will_set_the_zeroth_bit) {

    unsigned long actual[2] = { };
    long int bit_to_set = 0;
    unsigned long expected[2] = {1L, 0L};

    bit_field_set_bit(actual, bit_to_set);

    ck_assert_int_eq(memcmp(expected, actual, 2), 0);
} END_TEST

START_TEST(bit_field_set_bit_will_set_the_hundredth_bit) {

    unsigned long actual[2] = { };
    long int bit_to_set = 100;
    int shift_ammount = 100 - (8 * sizeof(unsigned long));

    unsigned long expected[2] = {0L, 1L << shift_ammount};

    bit_field_set_bit(actual, bit_to_set);

    ck_assert_int_eq(memcmp(expected, actual, 2), 0);
} END_TEST

int main() {
    Suite *s = suite_create("Bloom Filter");
    TCase *tc_bit_field = tcase_create("Bit Field");
    SRunner *sr = srunner_create(s);

    int num_fails;

    suite_add_tcase(s, tc_bit_field);

    tcase_add_test(tc_bit_field, bit_field_set_bit_will_set_the_zeroth_bit);
    tcase_add_test(tc_bit_field, bit_field_set_bit_will_set_the_hundredth_bit);

    srunner_run_all(sr, CK_NORMAL);
    num_fails = srunner_ntests_failed(sr);
    srunner_free(sr);

    return num_fails == 0 ? 0 : 1;
}
