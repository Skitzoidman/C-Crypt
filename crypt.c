//#define _XOPEN_SOURCE 700			//not entirely sure if needed; what does it do????

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<crypt.h>


struct cryptPasswd	{
	const char *key; 
	const char *salt;
};

struct cryptPasswd *createHash(const char *key, const char *salt)	{
	struct cryptPasswd *specificHash = malloc(sizeof(struct cryptPasswd));
	assert(specificHash != NULL);
	specificHash->key = key;
	specificHash->salt = salt;
	
	return specificHash;
};

int main(int argc, char *argv[])	{
	
		if(argc<3)	{
		printf("usage:	./crypt <password> <salt>\n");
	}
	
	const char *hash[100];
	struct cryptPasswd *user1 = createHash((const char *)argv[1],(const char *) argv[2]);

	if(argc == 3)	{
		*hash =(char *) crypt(user1->key, user1->salt);
		printf("%s\n", *hash);
	}	

	return 0;
}
