#include "bit_field.h"

void bit_field_set_bit(char *bits, long int bit_to_set) {

    long int index_in_bits = bit_to_set / 8;

    bits[index_in_bits] = 1;
}
