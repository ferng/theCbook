#include <stdio.h>

#define MAXLINE 1000

int getline(char s[], int lim);
int strrindex(char s[], char t[]);

char pattern[] = "ould";

main()
{
	int getline(char s[], int lim);
	int strrindex(char s[], char t[]);

	char line[MAXLINE];
	int found = 0, i;

	while (getline(line, MAXLINE) > 0)
		if ( (i = strrindex(line, pattern)) >= 0) {
			printf("%d:%s\n", i, line);
			found++;
		}
	return found;
}

int getline(char s[], int lim)
{
	int c, i;

	i=0;
	while (--lim >0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strrindex(char s[], char t[])
{
	int sLen, tLen, i, j, k;

	sLen = strlen(s) -1;
	tLen = strlen(t) -1;

	for (i = sLen; i > 0; i--){
		for (j = i, k = tLen; k != 0 && s[j] == t[k]; j--, k--)
			;
		if (k == 0)
			return i - tLen;
	}

	return -1;
}

