CC = gcc
LIBS = -lcrypto

AES: AES.o
	$(CC) $(LIBS) AES.o -o AES

AES.o: AES.c
	$(CC) -c AES.c

clean:
	rm -f AES AES.o
