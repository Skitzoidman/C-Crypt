//compile with -lcrypt !!!!
#define _XOPEN_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>

#define MAX_SIZE 20

/*FILE *shadowPw;
shadowPw = fopen("shadowPw.txt", "w"); //create new one
shadowPw = fopen("shadowPw.txt", "r+"); //read and update
shadowPw = fopen("shadowPw.txt", "r"); //read only
fclose("shadowPw");
*/
char *userPw[1];										//estimate required size
char *userName[1];
char buffPw[MAX_SIZE];
char buffName[MAX_SIZE];

struct userData	{
	char *name;
	char *pw;
};

struct cryptPw	{
	const char *crPw; 
	const char *crPwSalt;
};

struct cryptName	{
	const char *crName; 
	const char *crNameSalt;
};

struct cryptPw *createPwHash(const char *key, const char *salt)	{
	struct cryptPw *specificHash = malloc(sizeof(struct cryptPw));
	assert(specificHash != NULL);
	specificHash->crPw = key;
	specificHash->crPwSalt = salt;
	
	return specificHash;
}

struct cryptName *createNameHash(const char *key, const char *salt)	{
	struct cryptName *specificHash = malloc(sizeof(struct cryptName));
	assert(specificHash != NULL);
	specificHash->crName = key;
	specificHash->crNameSalt = salt;
	
	return specificHash;
}

struct userData *createData (char *uPw, char *uName)	{
	struct userData *user = malloc(sizeof(struct userData));
	assert(user!= NULL);
	user->pw = uPw;
	user->name = uName;	
	
	return user;
}

char clearPw(char *badPw)	{
	int stdinDump;
	memset(badPw, 0, MAX_SIZE);
	while(((stdinDump = getchar()) != '\n') && (stdinDump != EOF))	{
		continue;
	}
	return *badPw;
}

char clearName(char *badName)	{
	int stdinDump;
	memset(badName, 0, MAX_SIZE);
	while(((stdinDump = getchar()) != '\n') && (stdinDump != EOF))	{
		continue;
	}
	return *badName;
}

void readPw(char *pw)	{
	printf("Enter user password: \n");
	while(fgets(&pw[0], MAX_SIZE, stdin) != NULL)	{
		break;
	}
}

void readName(char *name)	{
	printf("Enter user name: \n");
	while(fgets(&name[0], MAX_SIZE, stdin) != NULL)	{
		break;
	}
}

char *getUserPw()	{
	extern char buffPw[MAX_SIZE];
	
getPw:
	readPw(buffPw);

	if((buffPw[18] != '\0' && buffPw[19] != '\n') || buffPw[19] != '\0' || buffPw[0] == '\0')	{
		printf("Password too long! Maximum of 18 characters allowed! \n");
		
		buffPw[MAX_SIZE] =  clearPw(buffPw);
		goto getPw;
	}
	return  buffPw;

}

char *getUserName()	{
	extern char buffName[MAX_SIZE];
	
getName:
	readName(buffName);

	if((buffName[18] != '\0' && buffName[19] != '\n') || buffName[19] != '\0' || buffName[0] == '\0')	{
		printf("Password too long! Maximum of 18 characters allowed! \n");
		
		buffName[MAX_SIZE] =  clearName(buffName);
		goto getName;
	}
	return  buffName;

}

int main(int argc, char *argv[])
{	
	const char *pwHash[1];
	const char *nameHash[1];
	*userName = getUserName();
	*userPw = getUserPw();

	struct userData *currUser = createData(*userPw, *userName);
	
	struct cryptName *currCryptNameUser = createNameHash((const char *) currUser->name,(const char *) argv[1]);

	struct cryptPw *currCryptPwUser = createPwHash((const char *) currUser->pw,(const char *) argv[2]);
	

	*nameHash = (char *) crypt(currCryptNameUser->crName, currCryptNameUser->crNameSalt);

	
	printf("nameHash: %s\n", *nameHash);
	printf("pwHash: %s\n", *pwHash);
	//free NameHash and pwHash buffer if u are pleased to, not really necessarry
	*nameHash = "\0";
	
	printf("nameHash: %s\n", *nameHash);
	printf("pwHash: %s\n", *pwHash);
//	free(currCryptNameUser);

	*pwHash = (char *) crypt(currCryptPwUser->crPw, currCryptPwUser->crPwSalt);
//	free(currCryptPwUser);
	printf("nameHash: %s\n", *nameHash);
	printf("pwHash: %s\n", *pwHash);

	return(0);
}


/*
	printf("userName in crypt struct: %s\n", currCryptNameUser->crName);
	printf("userNameSalt in crypt struct: %s\n", currCryptNameUser->crNameSalt);
	
	printf("userPw in crypt struct: %s\n", currCryptPwUser->crPw);
	printf("userPwSalt in crypt struct: %s\n", currCryptPwUser->crPwSalt)
*/