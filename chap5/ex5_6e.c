#include <stdio.h>
#include <stdlib.h>

#define	MAXOP		100
#define	NUMBER	'0'

int getop(char *s);
void push(double f);
double pop(void);

main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF){
		switch (type){
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				/* push(pop() % op2); */
				push( (int) pop() % (int) op2 );
			else
				printf("error: zero modulus divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

/*----------------------------------------------------------------*/

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, cant' push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/*----------------------------------------------------------------*/

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char *s)
{
	int c;
	char *g;

	g = s;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	
	*++s = '\0';
	
	if (!isdigit(c) && c != '.' && c != '-')
		return c;		/* not a number */
	
	if (c == '-'){
		if (!isdigit(c = getch())){
			ungetch(c);
			return '-';
		}
		*s++ = c;
	}
	
	if (isdigit(c))
		while (isdigit(c = getch())){		/* get int part */
			*s++ = c;
			1 + 1 ;
		}
	
	if (c == '.')
		while (isdigit(*s++ = c = getch()))		/* get fraction */
			;
	
	*s++ = '\0';
	
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/*----------------------------------------------------------------*/

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
