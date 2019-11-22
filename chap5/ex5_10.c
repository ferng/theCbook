#include <stdio.h>
#include <stdlib.h>

#define	MAXOP		100
#define	NUMBER	'0'

int getop(char *s);
void push(double f);
double pop(void);

int main(int argc, char *argv[])
{
	int type;
	double op2;

	while (--argc){
		switch (type = getop(*++argv)){
		case NUMBER:
			push(atof(*argv));
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
				push( (int) pop() % (int) op2 );
			else
				printf("error: zero modulus divisor\n");
			break;
		default:
			printf("error: unknown command %s\n", *argv);
			break;
		}
	}
	printf("\t%.8g\n", pop());
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

int getop(char *s)
{
	int c;

	c = *s++;
	
	if (!isdigit(c) && c != '.' && c != '-')
		return c;		/* not a number */
	
	if (c == '-'){
		if (!isdigit(c = *s++)){
			s--;
			return '-';
		}
	}
	
	if (isdigit(c))
		while (isdigit(*s++)) /* check int part */
			;
	
	if (c == '.')
		while (isdigit(c = *s++))		/* check fraction */
			;

	s--;

	if (*s)
		return -1;				/* there was more stuff after the number so not number */
	
	return NUMBER;
}
