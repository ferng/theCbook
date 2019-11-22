#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int rev(char to[], char from[], int len);

main()
{
	int len;
	char line[MAXLINE], dest[MAXLINE];

	while ( (len = getline(line, MAXLINE)) > 0){
		rev(dest, line, len);
		printf("%s", dest);
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

int rev(char to[], char from[], int len)
{
	int i, toPos;
	char tmp;

	toPos = 0;

	for ( i = len-1; i >= 0; --i){
		tmp = from[i];
		to[toPos] = tmp;
		++toPos;
	}

	to[toPos] = '\0';

	return toPos;
}