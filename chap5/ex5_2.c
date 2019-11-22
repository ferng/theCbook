#include <stdio.h>

#define SIZE 		20
#define NOTNUM	0

int getfloat(float *pn);

main()
{
	int m, n, o;
	float array[SIZE];

	for (n = 0; n < SIZE && (o=getfloat(&array[n])) != EOF; n++)
		if (o == NOTNUM)
			n--;

	for (m = 0; m < n; m++)
		printf("element %d is %f\n", m, array[m]);

	return 0;
}

/*----------------------------------------------------------------*/

int getch(void);
void ungetch(int);

#include <ctype.h>

int getfloat(float *pn){
	
	int c, sign;
	float power;

	while (isspace(c = getch()))
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
		return NOTNUM;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-'){
		c = getch();
		if (!isdigit(c)){
			return NOTNUM;
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	if (c == '.'){
		c = getch();
		for (power = 1.0; isdigit(c); c = getch()){
			*pn = 10 * *pn + (c - '0');
			power *= 10.0;
		}
		*pn /= power;
	}

	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}

#define	BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
