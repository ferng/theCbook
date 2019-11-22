#include <stdio.h>

#define MAXLINE 1000

int itoa(int n, char s[], int minLen);
void rev(char *to, char *from, int len);

main()
{
	int len;
	char line[MAXLINE];

	itoa(-127, line, 16);

	printf("%s", line);

	getchar();
	return 0;
}

int itoa(int n, char s[], int minLen)
{
	int i, sign;
	char s2[MAXLINE];

	if ((sign = n) < 0)
		n = -n;
	i = 0;

	do {
		s2[i++] = n % 10 + '0';
	} while ((n /= 10.0) > 0);

	for (; i<= minLen-1; i++)
		s2[i] = '0';
	
	if (sign < 0)
		s2[i++] = '-';

	s2[i] = '\0';

	rev(s, s2, i);

}


void rev(char *to, char *from, int len)
{
	char tmp;

	for ( from += len; len; --len){
		tmp = *--from;
		*to++ = tmp;
	}

	*to = '\0';
}
