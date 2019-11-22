#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int getline(char s[], int lim);
double atof(char s[]);

main()
{
	int getline(char s[], int lim);
	double atof(char s[]);

	char line[MAXLINE];
	double value;

	while (getline(line, MAXLINE) > 0)
	{
		value = atof(line);
		printf("%s : %f\n", line, value);
	}
}

int getline(char s[], int lim)
{
	int c, i;

	i=0;
	while (--lim >0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}


double atof(char s[])
{
	double val, power, expMult;
	int i, j, sign, exp;

	for (i = 0; isspace(s[i]); i++)			/* skip whitespace */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val +(s[i] - '0');
		power *= 10.0;
	}
	if (s[i++] == 'e' || s[i] == 'E') {
		expMult = (s[i] == '-') ? 10.0 : 0.1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for (exp = 0; isdigit(s[i]); i++)		
			exp = 10 * exp + (s[i] - '0');
		for (j = 1 ; j <= exp; j++){
				power *= expMult;
			}
	}

	return sign * val / power;
}
