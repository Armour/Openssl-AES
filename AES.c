#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char indata[AES_BLOCK_SIZE];
unsigned char outdata[AES_BLOCK_SIZE];
unsigned char userkey[] = "8Pw6wNc7x6smLffQ";
unsigned char IV[] = "FuySbnfey2eDSwe7";

void encrypt(void) {
	FILE *ifp, *ofp;
	ifp = fopen("signature", "r+");
	ofp = fopen("encrypted", "w+");
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
	fclose(ifp);
	fclose(ofp);
}

int main(void) {
	encrypt();
}
