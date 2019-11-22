#include <stdio.h>

#define TABSTOP		8
#define SPACE			'_'			/* so it's visible */
#define MAXLEN    1000
#define OUTSPACE	0
#define INSPACE		1

int getLine(char text[], int maxlen);
int deTab(char text[], char formatted[], int len, int tabs[]);
int enTab(char text[], char formatted[], int len, int tabs[]);

int main(int argc, char *argv[])
{
	char text[MAXLEN];
	char formatted[MAXLEN];
	char newText[MAXLEN];
	int pos, len, newlen, i=0, tabs[20];

	if (argc < 2){
		printf("\nerror: usage: prog {tablist}");
		return 0;
	}

	while (--argc){
		if (! (tabs[i++] = atoi(*++argv))){
			printf("\nerror: {tablist}: pos int, pos int, ...");
			return 0;
		}
	}

	tabs[i] = tabs[i-1] + (TABSTOP - (tabs[i-1] % TABSTOP));

	while (tabs[i++] < 72)
		tabs[i] = tabs[i-1] + 8;
	tabs[i] = '\0';
	
	while ((len = getLine(text,MAXLEN)) > 0){
		newlen = deTab(text, formatted, len, tabs);

		/* we're using the previous output as input saves us pissing about */

		len = enTab(formatted, newText, newlen, tabs);
		printf("%s%s", formatted, newText);
	}

	getchar();
	return 0;
}

int getLine(char text[], int maxlen)
{
	int c, i;

	for (i = 0; i < maxlen-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		text[i] = c;
	if (c =='\n'){
		text[i] = c;
		++i;
	}

	text[i] = '\0';
	return i;
}

int deTab(char text[], char formatted[], int len, int tabs[])
{
	int to, i, from, tabPos ;

	to = 0;

	for (from = 0; from < len; ++from){
		if (text[from] != '\t'){
			formatted[to] = text[from];
			i = ++to;
		}
		else{
			tabPos = 0;

			while (to > tabs[tabPos++])
				;
			
			to = tabs[tabPos-1];

			for (; i<=to; ++i)
				formatted[i] = SPACE;
		}
	}

	formatted[i] = '\0';

	return to;
}

int enTab(char text[], char formatted[], int len, int tabs[])
{
	int from, state, spaceStart, to, tabPos;

	spaceStart = to = tabPos = 0;
	state = OUTSPACE;

	for (from = 0; from < len; ++from, ++to){
		if ( ((from % tabs[tabPos]) == 0) && (state == INSPACE) ){
			to = spaceStart;
			formatted[to++] = '\t';
			state = OUTSPACE;
		}

		if (text[from] == SPACE){
			if (state == OUTSPACE){
				spaceStart = to;
				state = INSPACE;
			}
		}
		else{
			state = OUTSPACE;
		}
		formatted[to] = text[from];

		while (to > tabs[tabPos++])
			;
		tabPos--;
	}

	formatted[to] = '\0';

	return to;
}
