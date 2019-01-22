/*FILE *shadowPw;
shadowPw = fopen("shadowPw.txt", "w"); //create new one
shadowPw = fopen("shadowPw.txt", "r+"); //read and update
shadowPw = fopen("shadowPw.txt", "r"); //read only
fclose("shadowPw");
*/

#include<stdio.h>
#include<stdlib.h>

struct file	{
	FILE *shadowPw;
}pwFile;

void createFile(struct file pwFile)	{
	pwFile.shadowPw = fopen("/home/skit/Documents/C/Crypt/shadowPw.txt", "w");
	fclose(pwFile.shadowPw);
}

void writeFile(struct file pwFile, char *test)	{
	pwFile.shadowPw = fopen("/home/skit/Documents/C/Crypt/shadowPw.txt", "r+");
	fwrite(test, sizeof(test), 1, pwFile.shadowPw);
//	fputs ("hashkeks",pwFile.shadowPw);
	fclose(pwFile.shadowPw);
}

int main(int argc, char *argv[])	{
	createFile(pwFile);
	writeFile(pwFile);
//	pwFile.shadowPw = fopen("/home/skit/Documents/C/Crypt/shadowPw.txt", "w");
	//fwrite instead of fputs
//	fputs ("hashkeks",pwFile.shadowPw);
	return 0;
}