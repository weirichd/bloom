#include "hash_test.h"

#include "hash.h"

#include <check.h>

START_TEST(hash_will_return_differnet_ints_for_very_different_strings_with_the_same_function_number) {
    char *string1 = "David";
    char *string2 = "Weirich";

    uint32_t h1 = hash(0, string1);
    uint32_t h2 = hash(0, string2);

    ck_assert_int_ne(h1, h2);
} END_TEST

START_TEST(hash_will_return_differnet_ints_for_the_same_string_with_differnt_function_numbers) {
    char *string = "David";

    uint32_t h1 = hash(0, string);
    uint32_t h2 = hash(1, string);

    ck_assert_int_ne(h1, h2);
} END_TEST

TCase *create_hash_test_case() {
    TCase *tc= tcase_create("Hash");

    tcase_add_test(tc, hash_will_return_differnet_ints_for_very_different_strings_with_the_same_function_number);
    tcase_add_test(tc, hash_will_return_differnet_ints_for_the_same_string_with_differnt_function_numbers);

    return tc;
}
