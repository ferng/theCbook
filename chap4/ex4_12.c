#include <stdio.h>

void itoa(int n, char s[]);

int main()
{
	char s[12];

	itoa(-23,s);
	printf("%s",s);
	return 0;
}

void itoa(int n, char s[])
{
	static int charPos=0;

	if (n < 0){
		s[charPos++] = '-';
		n = -n;
	}
		
	if (n / 10)
		itoa(n / 10, s);
	s[charPos++] = (n % 10) + '0';
	s[charPos] = '\0';
}

