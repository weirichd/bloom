#ifndef BLOOM_H
#define BLOOM_H

#include <stdint.h>

typedef struct {
    uint32_t size;
    uint32_t hash_function_count;
} bloom_filter_t;

bloom_filter_t *bloom_create(int capacity, double false_positive_rate);

int bloom_contains(const bloom_filter_t* bloom, const char* str);

void bloom_destroy(bloom_filter_t *filter);

#endif // BLOOM_H
