CC=cc
CFLAGS=-g -Wall
LDFLAGS=-lcrypto -lssl

bogohash: bogohash.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm ./bogohash
