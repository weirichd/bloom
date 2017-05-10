#include "hash.h"

/* Bob Jenkin's One-at-a-time hash function source:
 *      https://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time
 *      http://www.burtleburtle.net/bob/hash/doobs.html
 */
uint32_t one_at_a_time(const char *str) {
    uint32_t h = 0;

    while(*str) {
        h += *str++;
        h += h << 10;
        h ^= h >> 6;
    }

    h += h << 3;
    h ^= h >> 11;
    h += h << 15;

    return h;
}

uint32_t davids_dumb_hash(const char *str) {
    const uint32_t a_big_prime_number = 0x0600BC09;

    uint32_t h = a_big_prime_number;

    while(*str) {
        h += *str++;
    }

    return h;
}

uint32_t hash(int function_number, const char *str) {
    return one_at_a_time(str) + function_number * davids_dumb_hash(str);
}
