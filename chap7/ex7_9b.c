#include	<ctype.h>
#include	<stdio.h>
#include	<stdlib.h>

#define		MAXLINE			70

int main()
{
	char c, line[MAXLINE], *pLine, i;
	int count = 0;

	pLine = line;

	while (fgets(line, MAXLINE, stdin) != NULL) {
		i = 0;
		while ((c = *(pLine+i)) != '\n') {
			if (c >= 'A' && c <= 'Z')
				count++;
			i++;
		}
	}
	printf("this many: %d\n", count);
	return 0;
}
