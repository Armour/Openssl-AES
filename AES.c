#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char indata[AES_BLOCK_SIZE];
unsigned char outdata[AES_BLOCK_SIZE];
unsigned char decryptdata[AES_BLOCK_SIZE];
unsigned char userkey[] = "\x09\x8F\x6B\xCD\x46\x21\xD3\x73\xCA\xDE\x4E\x83\x26\x27\xB4\xF6";
unsigned char IV[] = "\x0A\x91\x72\x71\x6A\xE6\x42\x84\x09\x88\x5B\x8B\x82\x9C\xCB\x05";

AES_KEY key;

void encrypt(void) {
    FILE *ifp, *ofp;
    ifp = fopen("signature", "r+");
    ofp = fopen("encrypted", "w+");
    int postion = 0;
    int bytes_read, bytes_write;
    while (1) {
        unsigned char ivec[AES_BLOCK_SIZE];
        memcpy(ivec, IV, AES_BLOCK_SIZE);
        bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);
        AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &postion, AES_ENCRYPT);
        bytes_write = fwrite(outdata, 1, bytes_read, ofp);
        if (bytes_read < AES_BLOCK_SIZE)
            break;
    }
    fclose(ifp);
    fclose(ofp);
}

void decrypt(void) {
    FILE *ifp, *ofp;
    ifp = fopen("encrypted", "r+");
    ofp = fopen("decrypted", "w+");
    int postion = 0;
    int bytes_read, bytes_write;
    while (1) {
        unsigned char ivec[AES_BLOCK_SIZE];
        memcpy(ivec, IV, AES_BLOCK_SIZE);
        bytes_read = fread(outdata, 1, AES_BLOCK_SIZE, ifp);
        AES_cfb128_encrypt(outdata, decryptdata, bytes_read, &key, ivec, &postion, AES_DECRYPT);
        bytes_write = fwrite(decryptdata, 1, bytes_read, ofp);
        if (bytes_read < AES_BLOCK_SIZE)
            break;
    }
    fclose(ifp);
    fclose(ofp);
}

int main(void) {
    AES_set_encrypt_key(userkey, 128, &key);
    encrypt();
    decrypt();
}
