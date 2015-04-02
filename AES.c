#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;

// Fill in actual key here
static const uchar ckey[] = "\x12\x12";

unsigned char indata[AES_BLOCK_SIZE];
unsigned char outdata[AES_BLOCK_SIZE];
unsigned char userkey[] = "8Pw6wNc7x6smLffQ";
unsigned char IV[] = "FuySbnfey2eDSwe7";

int main(void) {
	AES_KEY key;
	AES_set_encrypt_key(userkey, 128, &key);
	int postion = 0;
	int bytes_read, bytes_write;
	while (1) {
		bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);
		AES_cfb128_encrypt(indata, outdata, bytes_read, &key, IV, &postion, AES_ENCRYPT);
		bytes_write = fwrite(outdata, 1, bytes_read, ofp);
	    if (bytes_read < AES_BLOCK_SIZE)
			break;
	}
}
