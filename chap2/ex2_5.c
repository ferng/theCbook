#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int procLine(char line[], char findList[]);

main()
{
	char line[MAXLINE], findList[MAXLINE];

	findList[0] = 'a';
	findList[1] = 'e';
	findList[2] = 'i';
	findList[3] = 'o';
	findList[4] = 'u';
	findList[5] = '\0';

	while (getline(line, MAXLINE) > 0){
		printf("\n%d\n", procLine(line, findList) );
	}
	getchar();
	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';

	return i;
}

int procLine(char line[], char findList[])
{
	int i=0, j=0, findPos;
	char d;

	while (line[i] != '\0'){
		findPos=0;
		while ( (d=findList[findPos]) != '\0' && line[i] != d)
			findPos++;

		if (d != '\0')		/* didn't reached of chars to find so found a char */
			return i;

		i++;
	}

	return -1;
}
