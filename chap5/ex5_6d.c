#include <stdio.h>

#define MAXLINE 1000

int getline(char s[], int lim);
int strrindex(char *s, char *t);

char pattern[] = "ould";

main()
{
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

int strrindex(char *s, char *t)
{
	char *start, *currS, *currT;

	for (start = s; *s; s++){
		for (currS = s, currT = t; *currT && *currS++ == *currT++;)
			;
		if (! *currT)
			return s - start;
	}

	return -1;
}

