#include <stdio.h>

#define MAXLEN 100

void strncpy2(char *s, char *t, int n);

int main()
{
	char str1[MAXLEN] , str2[MAXLEN] = "well";

	strncpy2(str1, str2, 9);

	printf ("the final string is:\n%s",str1);

	return 0;
}


void strncpy2(char *s, char *t, int n)
{
	while ((*s++ = *t++)  && --n)
		;

	*s = '\0';
}
