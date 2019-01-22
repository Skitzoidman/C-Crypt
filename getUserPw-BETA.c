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
int j =  0;

char clearPw(char *badPw)	{
	
/*		printf("entering clearPw()\n");
		for(j = 0; j < MAX_PW_LENGTH; j++)	{
		printf("buffPw[%d]: %d\n", j, buffPw[j]);
		}	
		printf("\n");
*/	
		int ch;
	
/*		int i;
		for(i = 0; i < MAX_PW_LENGTH; i++)	{
			badPw[i] = 0;	
		}
*/
			
		memset(badPw, 0, MAX_PW_LENGTH);
		
		while(ch = getchar() != '\n' && ch != EOF)	{
			continue;
		};	
	
/*		printf("after clear\n");
		for(j = 0; j < MAX_PW_LENGTH; j++)	{
			badPw[j] = 0;
			printf("badPw[%d]: %d\n", j, badPw[j]);
			
		}
		printf("\n");
*/
		return *badPw;
}

		
		
		


	
char *readPw(char *Pw)	{
/*		printf("entering readPw;\n");
		for(j = 0; j < MAX_PW_LENGTH; j++)	{
			printf("Pw[%d]: %d\n", j, Pw[j]);
		}
		printf("\n");
*/	
		printf("Enter user password: \n");
	
/*		printf("\n");	
		printf("calling fgets\n");
*/		
		static char currPw[MAX_PW_LENGTH];
		int i;
		if(fgets(&Pw[0], MAX_PW_LENGTH, stdin) != NULL)	{
			for(i = 0; i < MAX_PW_LENGTH; i++)	{
				currPw[i] = Pw[i];
			}
		
/*			for(j = 0; j < MAX_PW_LENGTH; j++)	{
				printf("currPw[%d]: %d\n", j, currPw[j]);
			}
			printf("leaving fgets; return Pw\n");
			printf("going to check label\n");
*/			
		}
		return currPw;
};

char *getUserPw()	{
// MAX_PW_LENGTH --> MAX_Pw_SIZE
/*	printf("entering getUserPw()");
	printf("\n");
*/	
	extern char buffPw[MAX_PW_LENGTH];
	
/*	for(j = 0; j < MAX_PW_LENGTH; j++)	{
		printf("buffPw[%d]: %d\n", j, buffPw[j]);
	}	
	printf("\n");
*/
	
getPw:

/*	printf("entering getPw label\n");
	for(j = 0; j < MAX_PW_LENGTH; j++)	{
		printf("buffPw[%d]: %d\n", j, buffPw[j]);
	}
	
	printf("going to readPw\n");
	printf("\n");
*/	
	readPw(buffPw);
/*	printf("reading completed\n");
	
	printf("going to clearPw()\n");
	printf("\n");
*/	
	goto checkPw;

checkPw:
	
/*	printf("\n");
	printf("entering check label\n");
	for(j = 0; j < MAX_PW_LENGTH; j++)	{
		printf("buffPw[%d]: %d\n", j, buffPw[j]);
	}
	
	printf("check if(Pw overflow)\n");
*/	
	if((buffPw[18] != '\0' && buffPw[18] != '\n') || buffPw[18] != '\0' || buffPw[0] == '\0')	{
			printf("Password too long! Maximum of 18 characters allowed! \n");
		
//			printf("yes --> going to clearPw\n");
		
			buffPw[MAX_PW_LENGTH] =  clearPw(buffPw);
//			printf("going to getPw label\n");
			goto getPw;
	} else {
//		printf("no --> jumping to exit\n");
		goto exit;
	}

exit:	
	return  buffPw;

}


int main(int argc, char *argv[])	{
/*	printf("entering main\n");
	printf("going to getUserPw()\n");
	printf("\n");
*/
	
	*userPw = getUserPw();
//	printf("UserPw is: %s\n", *userPw);
	
	return 0;
}