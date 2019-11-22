#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	MAXOP		100
#define	NUMBER	'0'
#define	VAR			'1'

int getop(char[]);
void push(double);
void clear();
double pop(void);

main()
{
	int type;
	double op1, op2, recent;
	char s[MAXOP], vars[26];

	while ((type = getop(s)) != EOF){
		switch (type){
		case NUMBER:
			push(atof(s));
			break;
		case VAR:
			push(s[0]);
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
		case '#':
			push(recent);
			break;
		case 'p':
			recent = op2 = pop();
	/*		push(op2); */
			printf("\t%.8g\n", op2);
			break;
		case 'd':
			op2 = pop();
			push(op2);
			push(op2);
			break;
		case 's':
			op2 = pop();
			op1 = pop();
			push(op2);
			push(op1);
			break;
		case 'c':
			clear();
			break;
		case 'S':
			push(sin(pop()));
			break;
		case 'P':
			op2 = pop();
			push(pow(pop(),op2));
			break;
		case '>':
			op2 = pop();
			vars[(int)op2-'A'] = op1 = pop();
			push(op1);
			break;
		case '<':
			push(vars[((int)pop())-'A']);
			break;
		case '\n':
/*			printf("\t%.8g\n", pop()); */
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

void clear()
{
	sp = 0;
}

/*----------------------------------------------------------------*/

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (c == '$')					/* it's a math function */
		return c = getch();
	if (isupper(c))
		return VAR;
	if (!isdigit(c) && c != '.' && c != '-')
		return c;		/* not a number */
	i = 0;
	if (c == '-'){
		if (!isdigit(c = getch())){
			ungetch(c);
			return '-';
		}
		s[++i] = c;
	}
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))		/* get int part */
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))		/* get fraction */
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/*----------------------------------------------------------------*/

char charToReturn;
int holder;

int getch(void)
{
	charToReturn = (holder != 0) ? holder : getchar();
	holder = 0;
	return charToReturn;
}

void ungetch(int c)
{
	holder = c;
}
