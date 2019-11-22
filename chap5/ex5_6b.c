#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int htoi(char *line, int len);

main()
{
	int len, value;
	char line[MAXLINE];

	while ((len = getline(line, MAXLINE)) > 0){
		value = htoi(line, len-1);
		printf("\n%d %s\n", value, line);
	}

	getchar();
	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	s[i] = '\0';

	return i;
}

int htoi(char *line, int len)
{
	int c, num, val, digit;

	enum state{OK, BAD};

	num = val = 0;

	digit = OK;

	if ((*(line+1) == 'x') || (*(line+1) == 'X'))
		line += 2;

	for (len++; len && digit == OK; len--){
		if ((c = *line++) >= '0' && c <= '9')
			val = c - '0';
		else if (c >= 'A' && c <= 'F')
			val = c - 'A' + 10;
		else if (c >= 'a' && c <= 'f')
			val = c - 'a' + 10;
		else
			digit = BAD;

		num = 16 * num + val;
	}

	if (digit == BAD)
		return BAD;
	else
		return num;
}
