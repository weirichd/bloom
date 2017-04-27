#include "bit_field.h"

void bit_field_set_bit(char *bits, unsigned long int bit_to_set) {

    unsigned long int index_in_bits = bit_to_set / 8;
    unsigned char bit_in_byte_to_set = bit_to_set % 8;

    bits[index_in_bits] = 1 << bit_in_byte_to_set;
}
