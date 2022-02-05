# Moonstone
A cipher based on XOR cipher. <br>
Which using key, last number and length of data to decrypt the data. <br>
Still recommended to use another cipher such as AES, RSA etc. <br>

# How to use?
**Cipher** <br>
```
moonstone_cipher(tchr* dest, tchr* key, uint64_t* last_randnum, uint64_t* last_len)
dest = point to array contain a plain text.
key = point to array contain a key.
last_randnum = point to uint64_t variable that will receive last number.
last_len = point to uint64_t variable that will receive length of data.
```

**Decipher** <br>
```
moonstone_decipher(tchr* dest, tchr* key, uint64_t last_randnum, uint64_t last_len)
dest = point to array contain a cipher text.
key = point to array contain a key.
last_randnum = point to uint64_t variable that will used in decipher process.
last_len = point to uint64_t variable that will used in decipher process.
```

# Result
The result of ciphered text are different each sequence. <br>
Sequence 1:
```
Encrypted =>73Ps: sVHAR_M	32v7xnix$ %%	F]	WDE2$2*VVGGV__M(#%xv$P?94910i FSAA@\?:4;[G	@@MJ:0v%
P7>x,!,i

S$
PPccczXV?GG	H
^QVAPPM/78#%P3+,=*ei(i
S<5saFFV
FzGP	32v4	P:06x,;:*
FSBlgaz

Decrypted =NGC 1300 is a barred spiral galaxy located about 61 million light-years away in the constellation Eridanus. The galaxy is about 110,000 light-years across (about the half size of the Milky Way at 200,000). It is a member of the Eridanus Cluster, a cluster of 200 galaxies. It was discovered by John Herschel in 1835.
```
Sequence 2:
```
Encrypted ==40S\^]]PJ6w56P

Decrypted =NGC 1300 is a barred spiral galaxy located about 61 million light-years away in the constellation Eridanus. The galaxy is about 110,000 light-years across (about the half size of the Milky Way at 200,000). It is a member of the Eridanus Cluster, a cluster of 200 galaxies. It was discovered by John Herschel in 1835.
```

