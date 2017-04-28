#include "bloom_test.h"

#include "bloom.h"

#include <check.h>

START_TEST(bloom_create_gives_a_filter_with_good_values_for__bit_field_size_and_number_of_hashes) {
    int capacity = 10;
    double false_positive_rate = 0.1;
    int minimum_acceptable_size = 48;           // min_size = -capacity * ln(false_positive_rate) / ln(2)^2
    int minimum_acceptable_hash_count = 4;      // min_hash_count = -ln(false_positive_rate) / ln(2)

    bloom_filter_t *bloom = bloom_create(capacity, false_positive_rate);

    ck_assert_int_ge(bloom->size, minimum_acceptable_size);
    ck_assert_int_ge(bloom->hash_function_count, minimum_acceptable_hash_count);

    bloom_destroy(bloom);
} END_TEST

// source: http://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
inline int is_power_of_two(int number) {
    return (number & (number - 1)) == 0;
}

START_TEST(bloom_create_gives_a_filter_size_equal_to_a_power_of_2) {
    int capacity = 10;
    double false_positive_rate = 0.1;

    bloom_filter_t *bloom = bloom_create(capacity, false_positive_rate);

    ck_assert_msg(is_power_of_two(bloom->size), "bloom->size = %d which is not a power of 2", bloom->size);

    bloom_destroy(bloom);
} END_TEST

START_TEST(bloom_create_gives_a_filter_size_at_least_the_size_of_one_uint64_t) {
    int capacity = 1;
    double false_positive_rate = 0.99;

    bloom_filter_t *bloom = bloom_create(capacity, false_positive_rate);

    ck_assert_int_ge(bloom->size, 64);

    bloom_destroy(bloom);
} END_TEST

START_TEST(bloom_contains_returns_false_when_filter_is_empty) {
    int capacity = 10;
    double false_positive_rate = 0.1;
    bloom_filter_t *bloom = bloom_create(capacity, false_positive_rate);
    char *string = "David";

    int result = bloom_contains(bloom, string);
    bloom_destroy(bloom);

    ck_assert_msg(!result, "The empty filter reported that it did contain the string \"%s\".", string);

} END_TEST

inline void fill_bloom_filter_with_ones(bloom_filter_t *bloom) {
    size_t size_in_bytes = bloom->size / 8;
    memset(bloom->bits, 0xFF, size_in_bytes);
}

START_TEST(bloom_contains_returns_true_when_filter_is_totally_full) {
    int capacity = 10;
    double false_positive_rate = 0.1;
    bloom_filter_t *bloom = bloom_create(capacity, false_positive_rate);
    fill_bloom_filter_with_ones(bloom);
    char *string = "David";

    int result = bloom_contains(bloom, string);
    bloom_destroy(bloom);

    ck_assert_msg(result, "The filled filter reported that it did not contain the string \"%s\".", string);
} END_TEST

TCase *create_bloom_test_case() {
    TCase *tc= tcase_create("Bloom");

    tcase_add_test(tc, bloom_create_gives_a_filter_with_good_values_for__bit_field_size_and_number_of_hashes);
    tcase_add_test(tc, bloom_create_gives_a_filter_size_equal_to_a_power_of_2);
    tcase_add_test(tc, bloom_create_gives_a_filter_size_at_least_the_size_of_one_uint64_t);
    tcase_add_test(tc, bloom_contains_returns_false_when_filter_is_empty);
    tcase_add_test(tc, bloom_contains_returns_true_when_filter_is_totally_full);

    return tc;
}
