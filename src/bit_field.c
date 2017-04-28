#include "bit_field.h"

void bit_field_set_bit(uint64_t *bits, uint64_t bit_to_set) {

    uint64_t index_in_bits = bit_to_set / sizeof(uint64_t);
    char bit_in_byte_to_set = bit_to_set % sizeof(uint64_t);

    bits[index_in_bits] |= 1 << bit_in_byte_to_set;
}
