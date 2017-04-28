#include <check.h>
#include <stdint.h>

#include "bit_field.h"
#include "bloom.h"
#include "hash.h"

#include "bit_field_test.h"
#include "bloom_test.h"
#include "hash_test.h"

int main() {
    Suite *s = suite_create("Bloom Filter");

    SRunner *sr = srunner_create(s);

    suite_add_tcase(s, create_bit_field_test_case());
    suite_add_tcase(s, create_hash_test_case());
    suite_add_tcase(s, create_bloom_test_case());

    int num_fails;

    srunner_run_all(sr, CK_NORMAL);
    num_fails = srunner_ntests_failed(sr);
    srunner_free(sr);

    return num_fails == 0 ? 0 : 1;
}
