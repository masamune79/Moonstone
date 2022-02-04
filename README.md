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
![result](https://cdn.upload.systems/uploads/rohQlndr.gif)
