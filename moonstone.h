#ifndef MOONSTONE_H
#define MOONSTONE_H
#endif

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "tchar.h"

static uint64_t state = 0;

static void seed(uint64_t _seed) { state = _seed; }

static inline uint64_t sm64()
{
    uint64_t z = (state += 0x9E3779B97F4A7C15);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
    return z ^ (z >> 31);
}

bool moonstone_cipher(TCHAR* dest, TCHAR* key, uint64_t* last_randnum, uint64_t* last_len)
{
    uint64_t len_dest = _tcslen(dest);
    uint64_t len_key = _tcslen(key); 
    if (len_dest == 0 || len_key == 0) {return 0;}
    
    seed((uint64_t)time(0));
    uint64_t temp_randnum = sm64();
    uint64_t randnum = temp_randnum % len_key;
    if (randnum == 0) {randnum++;}
    
    uint64_t key_index = randnum;
    for (uint64_t i = 0; i < len_dest; i++)
    {
        key_index &= (randnum ^ i);
        key_index |= len_dest;
        dest[i] ^= key[((key_index ^ i) & len_dest) % randnum];
    }
    
    *last_randnum = temp_randnum;
    *last_len = len_dest;
    return 1;
}

bool moonstone_decipher(TCHAR* dest, TCHAR* key, uint64_t last_randnum, uint64_t last_len)
{
    if (last_randnum == 0 || last_len == 0) {return 0;}
    uint64_t len_key = _tcslen(key);
    uint64_t randnum = last_randnum % len_key;
    if (randnum == 0) {randnum++;}
    
    uint64_t key_index = last_randnum;
    for (uint64_t i = 0; i < last_len; i++)
    {
        key_index &= (randnum ^ i);
        key_index |= last_len;
        dest[i] ^= key[((key_index ^ i) & last_len) % randnum];
    }
    return 1;
}
