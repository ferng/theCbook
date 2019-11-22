#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max=0;
	while ((len = getline(line, MAXLINE)) > 0){
		if (len > max) {
			max=len;
			copy(longest, line);
		}
		printf("%d %s", len, line);
	}
	if (max > 0)
		printf("%d %s", max, longest);
	getchar();
	return 0;
}

int getline(char s[], int lim)
{
	int c, inLoop , i = 0;

	enum boolean { FALSE , TRUE };

	inLoop = TRUE;

	while (inLoop){
		if (i == lim)
			inLoop = FALSE;
		else
			if ( (c = getchar()) == '\n'){
				inLoop = FALSE;
				s[i++] = c;
			}
			else
				if (c == EOF)
					inLoop = FALSE;
				else
					s[i++] = c;
	}

	s[i] = '\0';

	return i;
}

void copy(char to[], char from[])
{
	int i;
	i=0;
	while ((to[i] = from[i]) != '\0')
		++i;
}