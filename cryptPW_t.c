#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>

//max 20: 18 Pw, 2 \0 and \n
#define MAX_PW_LENGTH 20
#define MAX_NAME_LENGTH 15

/*FILE *shadowPw;
shadowPw = fopen("shadowPw.txt", "w"); //create new one
shadowPw = fopen("shadowPw.txt", "r+"); //read and update
shadowPw = fopen("shadowPw.txt", "r"); //read only
fclose("shadowPw");
*/
char *userPw[1];										//estimate required size
char *userName[1];
char buffPw[MAX_PW_LENGTH];
char buffName[MAX_NAME_LENGTH];

struct userData	{
	char *name;
	char *Pw;
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
	user->Pw = uPw;
	user->name = uName;	
	
	return user;
}

char clearPw(char *badPw)	{
	int stdinDump;
	memset(badPw, 0, MAX_PW_LENGTH);
	while(((stdinDump = getchar()) != '\n') && (stdinDump != EOF))	{
		continue;
	}
	return *badPw;
}

void readPw(char *Pw)	{
	printf("Enter user password: \n");
	while(fgets(&Pw[0], MAX_PW_LENGTH, stdin) != NULL)	{
		break;
	}
}

char *getUserPw()	{
	extern char buffPw[MAX_PW_LENGTH];
	
getPw:
	readPw(buffPw);
	goto checkPw;

checkPw:
	if((buffPw[18] != '\0' && buffPw[18] != '\n') || buffPw[18] != '\0' || buffPw[0] == '\0')	{
		printf("Password too long! Maximum of 18 characters allowed! \n");
		
		buffPw[MAX_PW_LENGTH] =  clearPw(buffPw);
		goto getPw;
	} else {
		goto exit;
	}

exit:	
	return  buffPw;

}

char *getUserName()	{
	extern char buffName[MAX_NAME_LENGTH];
	printf("Enter user name: \n");
	fgets(buffName, MAX_NAME_LENGTH , stdin);
//	test if name was correctly written to buffer	
//	printf("%s\n", buffName);
	
	return  buffName;
}

//int i = 0;

int main(int argc, char *argv[])
{	
	const char *pwHash[100];
	const char *nameHash[100];
//	*userName = getUserName();
	*userPw = getUserPw();
	
//	test if getUserName worked correctly	
//	printf("Name is: %s \n", *userName);	
//	test if getUserPw worked correctly	
//	printf("Pw is: %s \n", *userPw);

	struct userData *currUser = createData(*userPw, *userName);
	
	struct cryptName *currCryptNameUser = createNameHash((const char *) currUser->name,(const char *) argv[1]);
//	printf("userName in crypt struct: %s\n", currCryptNameUser->crName);
	
	struct cryptPw *currCryptPwUser = createPwHash((const char *) currUser->Pw,(const char *) argv[1]);
	printf("userPw in crypt struct: %s\n", currCryptPwUser->crPw);


//	test if userPw was written to struct
	printf("%s\n", currUser->Pw);
	*pwHash =(char *) crypt(currCryptPwUser->crPw, currCryptPwUser->crPwSalt);
	printf("%s\n", *pwHash);

	return(0);
}