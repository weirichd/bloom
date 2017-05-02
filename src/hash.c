#include "hash.h"

const int a_big_prime_number = 0x0600BC09;

uint32_t hash(int function_number, const char *str) {
    uint32_t h1 = 0;
    uint32_t h2 = a_big_prime_number;

    while(*str) {
        h1 += *str;
        h2 ^= *str << 5;

        str++;
    }

    return h1 + h2*function_number;
}
