#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, NOBRACKETS };

int gettoken(void);

char validType[6][10] = {"char", "int", "float", "double", "void", ""};
char token[MAXTOKEN];
char out[1000], out2[1000];

int tokentype;

main()
{
	int type, foundPtr, i;
	char temp[MAXTOKEN], temp2[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		foundPtr = 0;
		while ((type = gettoken()) !=  '\n' ){
			if (type == PARENS || type == BRACKETS){
				strcat(out, token);
				foundPtr = 0;
			}
			else if (type == '*') {
				sprintf(temp, "(*%s)", out);
				sprintf(temp2, "*%s", out);
				strcpy(out, temp);
				strcpy(out2, temp2);
				foundPtr = 1;
			}
			else if (type == NAME) {
				for (i = 0;
							(validType[i][0] != '\0') && !(strcmp(token,validType[i]) == 0); 
							i++);
				if (validType[i][0] != '\0' && (foundPtr)){
						sprintf(temp, "%s %s", token, out2);
				}
				else
					sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
				foundPtr = 0;
			}
			else{
				printf("error: invalid input at %s\n", token);
				foundPtr = 0;
			}
		}
		printf("%s\n", out);
	}
	return 0;
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


