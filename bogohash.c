#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

void bogohash(char*,size_t);

int main(int argc, char** argv){
	bogohash(argv[1],strlen(argv[1]));
}

char* bin2hex(char* buffer, int len)
{
	char* outbuf = calloc(512,1);
	char* p = outbuf;
	for(int i = 0; i < len; i++)
	{
		sprintf(p,"%0.2x",buffer[i]);
		p=p+2;
	}
	return outbuf;
}

bool validate(char* buffer)
{
	int result;
	result = strncmp("DE",buffer,2);
	if (result == 0){
		return true;
	}
	return false;
}

void bogohash(char* buffer, size_t size)
{
	unsigned char* hashbuf;
	int count = 0;
	hashbuf = malloc(512);
	//printf("Before: %s\n",buffer);
	SHA1(buffer, size, hashbuf);
	size = 20;
	while(!validate(hashbuf))
	{
	//	printf("Size: %li",size);
		switch(hashbuf[0]%5){
			case 1:
				SHA1(hashbuf,size,hashbuf);
				size=20;
				break;
			case 2:
				SHA224(hashbuf,size,hashbuf);
				size=28;
				break;
			case 3:
				SHA256(hashbuf,size,hashbuf);
				size=32;
				break;
			case 4:
				SHA512(hashbuf,size,hashbuf);
				size=64;
				break;
			default:
				SHA1(hashbuf,size,hashbuf);
				size=20;
				break;
		}
		count++;
	}
	printf("iter:%i size:%li hash:%s\n",count,size,bin2hex(hashbuf,size));
}
