#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, NOBRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);

int tokentype, i;
char validType[6][10] = {"char", "int", "float", "double", "void", ""};
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

main()
{
	while (gettoken() != EOF){
		for (i = 0;
						(validType[i][0] != '\0') && !(strcmp(token,validType[i]) == 0); 
						i++);
		if (validType[i][0] == '\0' && tokentype == NAME)
			printf("error: invalid data type\n");
		else {
			strcpy(datatype, token);
			out[0] = '\0';
			dcl();
			if (tokentype == NOBRACKETS)
				printf("error: missing ]\n");
			else if (tokentype != '\n')
				printf("error: syntax error\n");
			printf("\t%s: %s %s\n", name, out, datatype);
		}
		tokentype = 0;
		token[0] = name[0] = datatype[0] = out[0] = '\0';
	}
	return 0;
}


void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}


void dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");

	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

int getch(void);
void ungetch(int c);

int gettoken(void)
{
	int c;
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;

	if (c == '(') {
		while ((c = getch()) == ' ' || c == '\t')
			;
		ungetch(c);
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[') {
		tokentype = NOBRACKETS;
		for (*p++ = c; ((*p++ = c = getch()) != ']' && c != '[' && c != '\n'); ) { 
			if (*(p-1) == ' ' || *(p-1) == '\t')
				p--;
		}
		if (c == ']'){
			*p = '\0';
			tokentype = BRACKETS;
		}
		return tokentype;
	}
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}


#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("error: ungetch - too many characters\n");
	else
		buf[bufp++] = c;
}


