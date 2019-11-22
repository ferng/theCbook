#include <stdio.h>

#define TABSTOP		8
#define SPACE			'_'			/* so it's visible */
#define MAXLEN    1000
#define OUTSPACE	0
#define INSPACE		1

int getLine(char text[], int maxlen);
int deTab(char text[], char formatted[], int len);
int enTab(char text[], char formatted[], int len);

main()
{
	char text[MAXLEN];
	char formatted[MAXLEN];
	int len, newlen;

	while ((len = getLine(text,MAXLEN)) > 0){
		newlen = deTab(text, formatted, len);

		/* we're using the previous output as input saves us pissing about */

		len = enTab(formatted, text, newlen);
		printf("%s%s", formatted, text);
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

int deTab(char text[], char formatted[], int len)
{
	int to, i, from ;

	to = 0;

	for (from = 0; from < len; ++from){
		if (text[from] != '\t'){
			formatted[to] = text[from];
			i = ++to;
		}
		else{
			i = to;
			to = ( ( (to / TABSTOP) + 1) * TABSTOP);

			for (; i<=to; ++i)
				formatted[i] = SPACE;
		}
	}

	formatted[i] = '\0';

	return to;
}

int enTab(char text[], char formatted[], int len)
{
	int from, state, spaceStart, to;

	spaceStart = to = 0;
	state = OUTSPACE;

	for (from = 0; from < len; ++from, ++to){
		if ( ((from % TABSTOP) == 0) && (state == INSPACE) ){
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
	}

	formatted[to] = '\0';

	return to;
}

