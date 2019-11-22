#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
	char *word;
	int count;
} keytab[] = {
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "do", 0 },
	{ "double", 0 },
	{ "else", 0 },
	{ "enum", 0 },
	{ "extern", 0 },
	{ "float", 0 },
	{ "for", 0 },
	{ "goto", 0 },
	{ "if", 0 },
	{ "int", 0 },
	{ "long", 0 },
	{ "register", 0 },
	{ "return", 0 },
	{ "short", 0 },
	{ "signed", 0 },
	{ "sizeof", 0 },
	{ "static", 0 },
	{ "struct", 0 },
	{ "switch", 0 },
	{ "typedef", 0 },
	{ "union", 0 },
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 },
};

#define	NKEYS			(sizeof keytab / sizeof(struct key))
#define	MAXWORD		100

int getword(char *word, int lim);
int binsearch(char *word, struct key keytab[], int n);

main()
{
	int n;
	char word[MAXWORD];
	
	while (getword(word, MAXWORD) != EOF){
 		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	}
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);

	return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
	int cond, low, high, mid;

	low = 0;
	high = n -1;
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getch(void);
void ungetch(int c);

int getword(char *word, int lim)
{
	int c, getch(void);
	static int inQuote = 0;
	static int Quote = 0;
	void ungetch(int);
	char *w = word;

	while	(isspace(c = getch()))
		;

	if(inQuote)
		*w++ = '"';

	if (c != EOF)
		*w++ = c;

	if (c == '#'){
		while (c = getch() != '\n')
			;
		ungetch(c);
		return '#';
	}
	else if (c == '/'){
		c = getch();
		if (c != '*')
			ungetch(c);
		else																	/* we're in a comment */
			for ( ; --lim > 0;){
				if ((c = getch()) == '*'){
					if ((c = getch()) == '/')
						return c;									
					else{
						ungetch(c);
						lim++;
					}
				}
			}							
	}
	else if (c == '\''){
		if ((c = getch()) == '\\')
			c = getch();
		if (c != '\'')
			printf("error: getword: broken single quotes");
	}
	else if (c == '"')
		if (inQuote)
			inQuote = 0;
		else
			inQuote = 1;
	else if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}

	for ( ; --lim > 0; w++){
		*w = c = getch();
		if (c == '"' && !inQuote){
			ungetch(c);
			break;
		}
		if (c == '"' && inQuote) {
			inQuote = 0;
			break;
		}
		if (!isalnum(c) && c != '_') {
			ungetch(c);
			break;
		}
	}
	*w = '\0';
	return word[0];
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
		printf("error: ungetch: too many chars\n");
	else
		buf[bufp++] = c;
}

