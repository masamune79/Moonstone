#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>

// char = 8, wchar_t = 16
#define CHAR_SET 16

#if CHAR_SET == 8
    typedef char tchr;
    #define _t(chr) chr
    #define _tcslen strlen
    #define _tprint printf
#elif CHAR_SET == 16
    typedef wchar_t tchr;
    #define _t(chr) L##chr
    #define _tcslen wcslen
    #define _tprint wprintf
#endif

uint64_t state = 0;

void seed(uint64_t _seed) { state = _seed; }

inline uint64_t sm64()
{
    uint64_t z = (state += 0x9E3779B97F4A7C15);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
    return z ^ (z >> 31);
}

inline uint64_t mix_sm64()
{
    time_t cur_time = time(0);
    seed((uint64_t)cur_time);
    uint64_t mix1 = sm64();
    seed((uint64_t)(time(0) & cur_time));
    uint64_t mix2 = sm64();
    return (mix1 ^ (cur_time % 10)) | mix2;
}

bool moonstone_cipher(tchr* dest, tchr* key, uint64_t* last_randnum, uint64_t* last_len)
{
    uint64_t len_dest = _tcslen(dest);
    uint64_t len_key = _tcslen(key); 
    if (len_dest == 0 || len_key == 0) {return 0;}
    
    uint64_t temp_randnum = mix_sm64();
    uint64_t randnum = temp_randnum % len_key;
    if (randnum == 0) {randnum++;}
    
    uint64_t key_index = randnum;
    for (uint64_t i = 0; i < len_dest; i++)
    {
        key_index %= (randnum ^ i);
        key_index |= (len_dest ^ i);
        dest[i] ^= key[((key_index ^ i) & len_dest) % randnum];
    }
    
    *last_randnum = temp_randnum;
    *last_len = len_dest;
    return 1;
}

bool moonstone_decipher(tchr* dest, tchr* key, uint64_t last_randnum, uint64_t last_len)
{
    if (last_randnum == 0 || last_len == 0) {return 0;}
    uint64_t len_key = _tcslen(key);
    uint64_t randnum = last_randnum % len_key;
    if (randnum == 0) {randnum++;}
    
    uint64_t key_index = last_randnum;
    for (uint64_t i = 0; i < last_len; i++)
    {
        key_index %= (randnum ^ i);
        key_index |= (last_len ^ i);
        dest[i] ^= key[((key_index ^ i) & last_len) % randnum];
    }
    return 1;
}

int main(int argc, char *argv[])
{
    // example data
    tchr data[512] = _t("NGC 1300 is a barred spiral galaxy located about 61 million light-years away in the constellation Eridanus. The galaxy is about 110,000 light-years across (about the half size of the Milky Way at 200,000). It is a member of the Eridanus Cluster, a cluster of 200 galaxies. It was discovered by John Herschel in 1835.");
    
    // example key
    tchr key[65] = _t("xq6FTYpgsEvwfUWJIO9tXQm0pUsNVR5TjL5Jmq7ApP2U3aYlh0ntgGKUv347SzkH");
    
    // please keep the last random number and lenght of data, it used when decryption process!
    uint64_t last_num = 0;
    uint64_t last_len = 0;
    	
    // warning!: print the encrypted char sometimes can corrupt std out buffer, which can corrupt decrypted char too
    moonstone_cipher(data, key, &last_num, &last_len);
   _tprint(_t("Encrypted = %ls\r\n" /* change this to %s when CHAR_SET is 8 */), data);
   
    moonstone_decipher(data, key, last_num, last_len);
    _tprint(_t("\r\nDecrypted = %ls" /* change this to %s when CHAR_SET is 8 */), data);
    
    return 1;
}
