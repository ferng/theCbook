#include <stdio.h>

#define MAXLEN 100

void strncat2(char *s, char *t, int n);

int main()
{
	char str1[MAXLEN] = "hello, ", str2[MAXLEN] = "world!";

	strncat2(str1, str2, 3);

	printf ("the final string is:\n%s",str1);

	return 0;
}


void strncat2(char *s, char *t, int n)
{
	while (*s++)
		;

	*s--;

	while ((*s++ = *t++)  && --n)
		;


}
