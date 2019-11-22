#include <stdio.h>

#define MAXLEN 100

void strcat2(char *s, char *t);

int main()
{
	char str1[MAXLEN] = "hello, ", str2[MAXLEN] = "world!";

	strcat2(str1, str2);

	printf ("the final string is:\n%s",str1);

	return 0;
}


void strcat2(char *s, char *t)
{
	while (*s++)
		;

	*s--;

	while (*s++ = *t++)
		;
	
}
