#include "hash.h"

uint32_t hash(int function_number, const char *str) {
    uint32_t h1 = 0;
    uint32_t h2 = 0;

    while(*str) {
        h1 += *str;
        h2 ^= *str;

        str++;
    }

    return h1 + h2*function_number;
}
