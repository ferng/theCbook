#include <stdio.h>

#define SIZE 		20
#define NOTNUM	0

int getint(int *pn);

main()
{
	int m, n, o, array[SIZE];

	for (n = 0; n < SIZE && (o=getint(&array[n])) != EOF; n++)
		if (o == NOTNUM)
			n--;

	for (m = 0; m < n; m++)
		printf("element %d is %d\n", m, array[m]);

	return 0;
}

/*----------------------------------------------------------------*/

int getch(void);
void ungetch(int);

#include <ctype.h>

int getint(int *pn){
	
	int c, sign;

	while (isspace(c = getch()))
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
/*		ungetch(c); */
		return NOTNUM;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-'){
		c = getch();
		if (!isdigit(c)){
/*			ungetch(c); */
			return NOTNUM;
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

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
