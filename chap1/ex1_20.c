#include <stdio.h>

#define TABSTOP		8
#define SPACE			'_'			/* so it's visible */
#define MAXLEN    1000

int getLine(char text[], int maxlen);
int deTab(char text[], char formatted[], int len);

main()
{
	char text[MAXLEN];
	char formatted[MAXLEN];
	int len, newlen;

	while ((len = getLine(text,MAXLEN)) > 0){
		newlen = deTab(text, formatted, len);
		printf("%d:%s%d:%s", len, text, newlen, formatted);
	}

	getchar();
	return 0;
}

int getLine(char text[], int maxlen)
{
	int c, i;

	for (i=0; i<maxlen-1 && (c=getchar())!=EOF && c!='\n'; ++i)
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

	for (from=0; from< len; ++from){
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