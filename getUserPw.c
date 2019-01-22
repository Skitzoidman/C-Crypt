#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>

#define MAX_PW_LENGTH 20
#define MAX_NAME_LENGTH 15

char buffPw[MAX_PW_LENGTH];
char *userPw[1];

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


int main(int argc, char *argv[])	{
	*userPw = getUserPw();
	
	return 0;
}