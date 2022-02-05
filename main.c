#include <stdio.h>
#include <stdint.h>
#include "moonstone.h"

int main()
{
    // example data
    TCHAR data[512] = _t("NGC 1300 is a barred spiral galaxy located about 61 million light-years away in the constellation Eridanus. The galaxy is about 110,000 light-years across (about the half size of the Milky Way at 200,000). It is a member of the Eridanus Cluster, a cluster of 200 galaxies. It was discovered by John Herschel in 1835.");
    
    // example key
    TCHAR key[65] = _t("xq6FTYpgsEvwfUWJIO9tXQm0pUsNVR5TjL5Jmq7ApP2U3aYlh0ntgGKUv347SzkH");
    
    // please keep the last random number and lenght of data, it used when decryption process!
    uint64_t last_num = 0;
    uint64_t last_len = 0;
      
    // warning!: print the encrypted char sometimes can corrupt std out buffer, which can corrupt decrypted char too
    moonstone_cipher(data, key, &last_num, &last_len);
   _tprint(_t("Encrypted =" STR "\r\n"), data);
   
    moonstone_decipher(data, key, last_num, last_len);
    _tprint(_t("Decrypted =" STR "\r\n"), data);
    
    return 1;
}
