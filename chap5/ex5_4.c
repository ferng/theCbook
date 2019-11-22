#include <stdio.h>

#define MAXLEN 100

int strend(char *s, char *t);

int main()
{
	char str1[MAXLEN] = "once upon a time", str2[MAXLEN] = "time";

	printf("\nthe string was ");

	if (! strend(str1, str2) )
		printf("not ");
	
	printf("found.");

	return 0;
}


int strend(char *s, char *t)
{
	int sOffset = 0, tOffset = 0;

	while ( *(s + sOffset++))
		;
	
	while ( *(t + tOffset++))
		;

	sOffset--;
	tOffset--;

	while ( ( *(s + --sOffset) == *(t + --tOffset) ) && sOffset )
		if (! tOffset)
			return 1;

	return 0;

}
