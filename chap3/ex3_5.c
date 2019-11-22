#include <stdio.h>

#define MAXLINE 1000

int itob(int n, char s[], int b);
int rev(char to[], char from[], int len);


main()
{
	int len;
	char line[MAXLINE];

	itob(255,line,16);

	printf("%s", line);

	getchar();
	return 0;
}


int itob(int n, char s[], int b)
{
	int i, sign;
	char s2[MAXLINE];

	if ((sign = n) < 0)
		n = -n;
	i = 0;

	do {
		s2[i++] = (n % b <= 9) ? (n % b) + '0' : (n % b) + -10 + 'A';
	} while ((n /= b) > 0);

	if (sign < 0)
		s2[i++] = '-';

	s2[i] = '\0';

	rev(s, s2, i);
}


int rev(char to[], char from[], int len)
{
	int i, toPos;
	char tmp;

	toPos = 0;

	for ( i = len-1; i >= 0; --i){
		tmp = from[i];
		to[toPos] = tmp;
		++toPos;
	}

	to[toPos] = '\0';

	return toPos;
}
