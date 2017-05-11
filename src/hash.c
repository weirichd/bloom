#include "hash.h"

/* Bob Jenkin's One-at-a-time hash function source:
 *      https://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time
 *      http://www.burtleburtle.net/bob/hash/doobs.html
 */
uint32_t one_at_a_time(const char *str, int seed) {
    uint32_t h = seed;

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

uint32_t hash(int function_number, const char *str) {
    return one_at_a_time(str, function_number);
}
