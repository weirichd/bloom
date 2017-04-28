#include "bloom.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

const double ln_2 = 0.69314718055994530941723212145817656807550013436025525412;

// source: https://en.wikipedia.org/wiki/Bloom_filter#Optimal_number_of_hash_functions
inline double calculate_required_number_of_hashes(double false_positive_rate) {
    return -log(false_positive_rate) / ln_2;
}

inline double calculate_required_bit_field_size(int capacity, double false_positive_rate) {
    return - capacity * log(false_positive_rate) / (ln_2 * ln_2);
}

// source: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
inline uint32_t next_power_of_two(uint32_t number) {
    number--;
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;
    number |= number >> 16;
    number++;

    return number;
}

inline size_t size_in_bytes(uint32_t size_in_bits) {
    return size_in_bits >> 3;
}

bloom_filter_t *bloom_create(int capacity, double false_positive_rate) {
    bloom_filter_t *filter = calloc(1, sizeof(bloom_filter_t));

    filter->hash_function_count = ceil(calculate_required_number_of_hashes(false_positive_rate));
    filter->size = ceil(calculate_required_bit_field_size(capacity, false_positive_rate));
    filter->size = next_power_of_two(filter->size);

    if(filter->size < sizeof(uint64_t) * 8)
        filter->size = sizeof(uint64_t) * 8;

    filter->bits = calloc(1, size_in_bytes(filter->size));

    return filter;
}

void bloom_destroy(bloom_filter_t *filter) {
    free(filter->bits);
    free(filter);
}

int bloom_contains(const bloom_filter_t* bloom, const char* str) {
    return bloom->bits[0];
}
