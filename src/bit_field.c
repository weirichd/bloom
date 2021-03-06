#include "bit_field.h"

inline uint32_t get_array_index_of_bit(uint32_t bit_index) {
    return bit_index / 64;
}

inline int get_bit_number_in_uint64(uint32_t bit_index) {
    return bit_index % 64;
}

inline uint64_t mask_single_bit(int bit_number) {
    return 1ULL << bit_number;
}

void bit_field_set_bit(uint64_t *bits, uint32_t bit_to_set) {
    uint32_t index = get_array_index_of_bit(bit_to_set);
    int bit_number = get_bit_number_in_uint64(bit_to_set);

    bits[index] |= mask_single_bit(bit_number);
}

int bit_field_is_set(const uint64_t *bits, uint32_t bit_to_check) {
    uint32_t index = get_array_index_of_bit(bit_to_check);
    int bit_number = get_bit_number_in_uint64(bit_to_check);

    return (bits[index] & mask_single_bit(bit_number)) != 0;
}
