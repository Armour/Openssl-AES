#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char indata[AES_BLOCK_SIZE];
unsigned char outdata[AES_BLOCK_SIZE];
unsigned char decryptdata[AES_BLOCK_SIZE];
unsigned char userkey[] = "8Pw6wNc7x6smLffQ";
unsigned char IV[] = "FuySbnfey2eDSwe7";

AES_KEY key;

void encrypt(void) {
	FILE *ifp, *ofp;
	ifp = fopen("signature", "r+");
	ofp = fopen("encrypted", "w+");
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
void decrypt(void) {
	FILE *ifp, *ofp;
	ifp = fopen("encrypted", "r+");
	ofp = fopen("decrypted", "w+");
	int postion = 0;
	int bytes_read, bytes_write;
	while (1) {
		bytes_read = fread(outdata, 1, AES_BLOCK_SIZE, ifp);
		AES_cfb128_encrypt(outdata, decryptdata, bytes_read, &key, IV, &postion, AES_DECRYPT);
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
