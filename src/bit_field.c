#include "bit_field.h"

void bit_field_set_bit(uint64_t *bits, uint64_t bit_to_set) {

    uint64_t index_in_bits = bit_to_set / sizeof(uint64_t);
    char bit_in_byte_to_set = bit_to_set % sizeof(uint64_t);

    bits[index_in_bits] |= 1 << bit_in_byte_to_set;
}

int bit_field_is_set(const uint64_t *bits, uint64_t bit_to_check) {
    uint64_t index_in_bits = bit_to_check / sizeof(uint64_t);
    char bit_in_byte_to_check = bit_to_check % sizeof(uint64_t);

    uint64_t mask = 1 << bit_in_byte_to_check;

    return (bits[index_in_bits] & mask) != 0;
}
