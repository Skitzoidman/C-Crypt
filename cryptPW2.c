#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>

//max 20: 18 PW, 2 \0 and \n
#define MAX_PW_LENGTH 20
#define MAX_NAME_LENGTH 15

/*FILE *shadowPW;
shadowPW = fopen("shadowPW.txt", "w"); //create new one
shadowPW = fopen("shadowPW.txt", "r+"); //read and update
shadowPW = fopen("shadowPW.txt", "r"); //read only
fclose("shadowPW");
*/
char *userPW[1];										//estimate required size
char *userName[1];
char buffPW[MAX_PW_LENGTH];
char buffName[MAX_NAME_LENGTH];

struct userData	{
	char *name;
	char *PW;
};

struct cryptPW	{
	const char *crPw; 
	const char *crPwSalt;
};

struct cryptName	{
	const char *crName; 
	const char *crNameSalt;
};

struct cryptPW *createPWHash(const char *key, const char *salt)	{
	struct cryptPW *specificHash = malloc(sizeof(struct cryptPW));
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

struct userData *createData (char *uPW, char *uName)	{
	struct userData *user = malloc(sizeof(struct userData));
	assert(user!= NULL);
	user->PW = uPW;
	user->name = uName;	
	
	return user;
}

char *getUserPW()	{
	extern char buffPW[MAX_PW_LENGTH];
	getPW:
	printf("Enter user password: \n");
	fgets(buffPW, MAX_PW_LENGTH , stdin);
//	test if PW was correctly written to buffer	
//	printf("%s\n", buffPW);
	
	if(buffPW[18] != '\0' && buffPW[18] != '\n')	{
		printf("Password too long! Maximum of 18 characters allowed! \n");
		int i;
		for(i = 0; i < 21; i++)	{
			buffPW[i] = 0;
		}
		goto getPW;
	}
	
	return  buffPW;
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
	*userName = getUserName();
	*userPW = getUserPW();
	
//	test if getUserName worked correctly	
//	printf("Name is: %s \n", *userName);	
//	test if getUserPW worked correctly	
//	printf("PW is: %s \n", *userPW);

	struct userData *currUser = createData(*userPW, *userName);
	
	struct cryptName *currCryptNameUser = createNameHash((const char *) currUser->name,(const char *) argv[1]);
//	printf("userName in crypt struct: %s\n", currCryptNameUser->crName);
	
	struct cryptPW *currCryptPWUser = createPWHash((const char *) currUser->PW,(const char *) argv[1]);
//	printf("userPW in crypt struct: %s\n", currCryptPWUser->crPw);


//	test if userPW was written to struct
//	printf("%s\n", currUser->PW);

	return(0);
}


	
//	test correct writing to buffPW	
/*	for(i = 0; i < 21; i++)	{
		if(userPW[i] != '\0')	{
			printf("%d: %c\n", i, userPW[i]);
		}
		if(userPW[i] == '\0' || userPW[i] == '\n')	{
			printf("%d: %d\n", i, userPW[i]);
		}	
	}
*/	