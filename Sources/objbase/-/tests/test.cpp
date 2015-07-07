#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream.h>
#include <stdarg.h>

int main (int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	char * fileName = "../Lay.h";
	FILE *srcFile = fopen (fileName,"r+b");
	if (srcFile==NULL)
	{
		printf ("\nError opening \"%s\"\n\n", fileName);
		return 0;
	}
	fseek(srcFile,0,SEEK_END);
	long nSrcLength=ftell(srcFile);
	fseek(srcFile,0,SEEK_SET);
	char * pStr = new char [nSrcLength+1];
	fread(pStr,nSrcLength,1,srcFile);
	//pStr[nSrcLength] = 0;
	pStr[100] = 0;
	fclose(srcFile);
	printf (pStr);

	return 0;
}