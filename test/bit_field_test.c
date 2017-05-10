#include "bit_field.h"

#include <check.h>
#include <stdint.h>

START_TEST(bit_field_set_bit_will_set_the_zeroth_bit) {
    uint64_t actual[2] = { };
    uint32_t bit_to_set = 0;
    uint64_t expected[2] = {1, 0};

    bit_field_set_bit(actual, bit_to_set);

    ck_assert_int_eq(memcmp(expected, actual, sizeof(actual)), 0);
} END_TEST

START_TEST(bit_field_set_bit_will_set_the_hundredth_bit) {
    uint64_t actual[2] = { };
    uint32_t bit_to_set = 100;
    uint64_t expected[2] = {0, 1ULL << 36};

    bit_field_set_bit(actual, bit_to_set);

    ck_assert_int_eq(memcmp(expected, actual, sizeof(actual)), 0);
} END_TEST

START_TEST(bit_field_set_bit_will_leave_already_set_bits_as_they_were) {
    uint64_t actual[2] = {1 << 30, 0};
    uint32_t bit_to_set = 0;
    uint64_t expected[2] = {1 << 30 | 1, 0};

    bit_field_set_bit(actual, bit_to_set);

    ck_assert_int_eq(memcmp(expected, actual, sizeof(actual)), 0);
} END_TEST

START_TEST(bit_field_is_set_will_return_false_when_a_field_is_not_set) {
    uint64_t bits[2] = {2, 0};
    uint32_t bit_to_check = 0;

    int result = bit_field_is_set(bits, bit_to_check);

    ck_assert_int_eq(result, 0);
} END_TEST

START_TEST(bit_field_is_set_will_return_true_when_a_field_is_set) {
    uint64_t bits[2] = {3, 0};
    uint32_t bit_to_check = 1;

    int result = bit_field_is_set(bits, bit_to_check);

    ck_assert_int_eq(result, 1);
} END_TEST

TCase *create_bit_field_test_case() {
    TCase *tc= tcase_create("Bit Field");

    tcase_add_test(tc, bit_field_set_bit_will_set_the_zeroth_bit);
    tcase_add_test(tc, bit_field_set_bit_will_set_the_hundredth_bit);
    tcase_add_test(tc, bit_field_set_bit_will_leave_already_set_bits_as_they_were);
    tcase_add_test(tc, bit_field_is_set_will_return_false_when_a_field_is_not_set);
    tcase_add_test(tc, bit_field_is_set_will_return_true_when_a_field_is_set);

    return tc;
}
