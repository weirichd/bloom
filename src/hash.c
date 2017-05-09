#include "hash.h"

const int a_big_prime_number = 0x0600BC09;

// Bob Jenkin's One-at-a-time hash function source: https://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time
//                                                  http://www.burtleburtle.net/bob/hash/doobs.html
uint32_t hash(int function_number, const char *str) {
    uint32_t h1 = 0;
    uint32_t h2 = a_big_prime_number;

    while(*str) {
        h1 += *str;
        h1 += h1 << 10;
        h1 ^= h1 >> 6;

        h2 ^= *str << 5;

        str++;
    }
    h1 += h1 << 3;
    h1 ^= h1 >> 11;
    h1 += h1 << 15;

    return h1 + h2 *(function_number + 1);
}
