# Moonstone
A cipher based on XOR cipher. <br>
Which using key, last number and length of data to decrypt the data. <br>
Still recommended to use another cipher such as AES, RSA etc. <br>

# How to use?
**Cipher** <br>
```
moonstone_cipher(__TCHAR* dest, __TCHAR* key, uint32_t* last_randnum, uint32_t* last_len)
dest = point to array contain a plain text.
key = point to array contain a key.
last_randnum = point to uint32_t variable that will receive last number.
last_len = point to uint32_t variable that will receive length of data.
```

**Decipher** <br>
```
moonstone_decipher(__TCHAR* dest, __TCHAR* key, uint32_t last_randnum, uint32_t last_len)
dest = point to array contain a cipher text.
key = point to array contain a key.
last_randnum = point to uint32_t variable that will used in decipher process.
last_len = point to uint32_t variable that will used in decipher process.
```

# Result
```
Encrypted = #Vv<>A4⁅x9&,*?=Rv#$V%(#99kx>9"_k#9V;>[)C%\k$PQ

Decrypted = The Kuril–Kamchatka Trench or Kuril Trench is an oceanic trench in the northwest Pacific Ocean. It lies off the southeast coast of Kamchatka and parallels the Kuril Island chain to meet the Japan Trench east of Hokkaido. It extends from a triple junction with the Ulakhan Fault and the Aleutian Trench near the Commander Islands, Russia, in the northeast, to the intersection with the Japan Trench in the southwest.
[Program finished]
```
