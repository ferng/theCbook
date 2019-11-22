#include <stdio.h>
#include <stdlib.h>

#define	MAXOP		100
#define	NUMBER	'0'

void push(double);
double pop(void);

main()
{
	int type;
	double op2, opX;
	char s[MAXOP];

	while (scanf("%s", s) != EOF){
		if (sscanf(s, "%lf", &opX) == 1)
			type = NUMBER;
		else
			type = s[0];
		switch (type){
		case NUMBER:
			push(opX);
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
		case 'p':
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

