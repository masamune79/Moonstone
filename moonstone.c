#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>

// char = 8, wchar_t = 16
#define CHAR_SET 16

#if CHAR_SET == 8
    typedef char __TCHAR;
    #define __TEXT(chr) chr
    #define __tcslen strlen
    #define _FNPUTS printf
#elif CHAR_SET == 16
    typedef wchar_t __TCHAR;
    #define __TEXT(chr) L##chr
    #define __tcslen wcslen
    #define _FNPUTS wprintf
#endif

static uint32_t state = 0;

void seed(uint32_t ss)
{
    state = ss;
}

uint32_t xorshift32(void)
{
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

bool moonstone_cipher(__TCHAR* dest, __TCHAR* key, uint32_t* last_randnum, uint32_t* last_len)
{
    size_t len_dest = __tcslen(dest);
    size_t len_key = __tcslen(key);
    
    if (len_dest == 0 || len_key == 0) {return 0;}
    
    seed((uint32_t)time(0));
    uint32_t temp_randnum = xorshift32();
    if (temp_randnum == 0) {temp_randnum = len_dest * len_key;}
    uint32_t randnum = temp_randnum % len_key;
    if (randnum == 0) {randnum++;}
    
    uint32_t key_index = randnum; 
    for (uint32_t i = 0; i < len_dest; i++)
    {
        key_index %= (randnum ^ i);
        key_index |= (len_dest ^ i);
        dest[i] ^= key[((key_index ^ i) & len_dest) % randnum];
    }
    
    *last_randnum = randnum;
    *last_len = len_dest;
    return 1;
}

bool moonstone_decipher(__TCHAR* dest, __TCHAR* key, uint32_t last_randnum, uint32_t last_len)
{
    if (last_randnum == 0 || last_len == 0) {return 0;}
    uint32_t key_index = last_randnum;
    for (uint32_t i = 0; i < last_len; i++)
    {
        key_index %= (last_randnum ^ i);
        key_index |= (last_len ^ i);
        dest[i] ^= key[((key_index ^ i) & last_len) % last_randnum];
    }
    return 1;
}

int main(int argc, char *argv[])
{
    // example data
    __TCHAR data[512] = __TEXT("The Kuril–Kamchatka Trench or Kuril Trench is an oceanic trench in the northwest Pacific Ocean. It lies off the southeast coast of Kamchatka and parallels the Kuril Island chain to meet the Japan Trench east of Hokkaido. It extends from a triple junction with the Ulakhan Fault and the Aleutian Trench near the Commander Islands, Russia, in the northeast, to the intersection with the Japan Trench in the southwest.");
    
    // example key Pf5xjPA4lj28zZ27PXCDcwy3VKbhwRsJ
    __TCHAR key[33] = __TEXT("Pf5xjPA4lj28zZ27PXCDcwy3VKbhwRsJ");
    
    // please keep the last random number and lenght of data, it used when decryption process!
    uint32_t last_num = 0;
    uint32_t last_len = 0;
	
    // warning!: print the encrypted char sometimes can corrupt std out buffer, which can corrupt decrypted char too
    moonstone_cipher(data, key, &last_num, &last_len);
    _FNPUTS(__TEXT("Encrypted = %ls" /* change this to %s when CHAR_SET is 8 */), data);
    
    moonstone_decipher(data, key, last_num, last_len);
    _FNPUTS(__TEXT("\r\nDecrypted = %ls" /* change this to %s when CHAR_SET is 8 */), data);
    
    return 1;
}
