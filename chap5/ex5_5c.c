#include <stdio.h>

#define MAXLEN 100

int strncmp2(char *s, char *t, int n);

int main()
{
	char str1[MAXLEN] = "morning ladies", str2[MAXLEN] = "morning gents";

	int a;

	a = strncmp2(str1, str2, 10);

	printf("\nthe first string is ");

	if (a < 0)
		printf("less than");
	else if (a == 0)
		printf("the same as");
	else
		printf("more than");

	printf(" the other string (well up to n chars anyway)");

	return 0;
}


int strncmp2(char *s, char *t, int n)
{
	for (;(*s == *t) && n; s++, t++, n--);

	if (!n)
		return 0;

	return *s - *t;
}
