#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>

void bit_field_set_bit(uint64_t *bits, uint64_t bit_to_set);
int bit_field_is_set(const uint64_t *bits, uint64_t bit_to_check);

#endif // BIT_FIELD_H
