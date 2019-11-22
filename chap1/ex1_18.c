#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int copy(char to[], char from[]);

main()
{
	int len;
	char line[MAXLINE], dest[MAXLINE];

	while ((getline(line, MAXLINE)) > 0){
		len = copy(dest, line);
		printf("%d %s", len, dest);
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

int copy(char to[], char from[])
{
	int i, lastPrintable;

	i = lastPrintable = 0;
	while ((from[i]) != '\0'){
		if (from[i] != ' ' && from[i] != '\t' && from[i] != '\n' ){
			lastPrintable = i;
		}
		++i;
	}

	for (i=0; i<= lastPrintable; i++)
		to[i] = from[i];

	to[i] = '\0';

	return lastPrintable;
}