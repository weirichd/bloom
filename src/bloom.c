#include "bloom.h"

#include "bit_field.h"
#include "hash.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const double ln_2 = 0.69314718055994530941723212145817656807550013436025525412;

// source: https://en.wikipedia.org/wiki/Bloom_filter#Optimal_number_of_hash_functions
inline double calculate_required_number_of_hashes(double false_positive_rate) {
    return -log(false_positive_rate) / ln_2;
}

inline double calculate_required_bit_field_size(int capacity, double false_positive_rate) {
    return -capacity * log(false_positive_rate) / (ln_2 * ln_2);
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

bloom_filter_t *bloom_create(int capacity, double false_positive_rate) {
    bloom_filter_t *filter = calloc(1, sizeof(bloom_filter_t));

    filter->hash_function_count = ceil(calculate_required_number_of_hashes(false_positive_rate));
    filter->size = ceil(calculate_required_bit_field_size(capacity, false_positive_rate));
    filter->size = next_power_of_two(filter->size);

    if(filter->size < sizeof(uint64_t) * 8)
        filter->size = sizeof(uint64_t) * 8;

    size_t bits_array_length = filter->size / (sizeof(uint64_t) * 8);

    filter->bits = calloc(bits_array_length, sizeof(uint64_t));

    return filter;
}

void bloom_destroy(bloom_filter_t *filter) {
    free(filter->bits);
    free(filter);
}

void bloom_put(bloom_filter_t *bloom, const char *str) {
    for(int i = 0; i < bloom->hash_function_count; i++) {
        uint32_t h = hash(i, str);
        h %= bloom->size;

        bit_field_set_bit(bloom->bits,  h);
    }
}

int bloom_contains(const bloom_filter_t* bloom, const char* str) {
    int found = 0;

    for(int i = 0; i < bloom->hash_function_count; i++) {
        uint32_t h = hash(i, str);
        h %= bloom->size;

        found |= bit_field_is_set(bloom->bits,  h);
    }

    return found;
}

inline void remove_newline(char *str) {
	str[strcspn(str, "\n")] = '\0';
}

void bloom_load_dictionary(bloom_filter_t *bloom, const char *file_path) {
	FILE *file;

	file = fopen(file_path, "r");

	char word[10] = {0};

	while(fgets(word, sizeof(word), file)) {
		remove_newline(word);
		bloom_put(bloom, word);
	}

	fclose(file);
}
