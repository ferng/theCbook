#include <stdio.h>

#define	MAXLEN			300
#define	OUT					0
#define	IN					1

int getLine(char line[], int max);
void procLine(char line[]);

main()
{
	char line[MAXLEN];

	while (getLine(line, MAXLEN) > 0)
		procLine(line);

	return 0;
}

int getLine(char line[], int max)
{
	int c, pos;

	for (pos = 0; ((c = getchar()) != EOF) && (c != '\n') && pos < max; ++pos)
		line[pos] = c;

	if (c == '\n'){
		line[pos] = c;
		++pos;
	}

	line[pos] = '\0';

	return pos;
}

void procLine(char line[])
{
	int comState, strState, inPos;
	int parenths, braces, brackets, singleq, doubleq;

	inPos = parenths = braces = brackets = singleq = doubleq = 0;
	comState = strState = OUT;

	while (line[inPos] != '\0'){

		if (line[inPos] == '/' && line[inPos+1] == '*' && strState == OUT)
			comState = IN;

		if (line[inPos] == '*' && line[inPos+1] == '/' && strState == OUT){
			comState = OUT;
		}

		if (line[inPos] == '"' && comState == OUT)
			if (strState == IN)
				strState = OUT;
			else
				strState = IN;

		if (comState == OUT){
			if ( line[inPos] == '\(' && line[inPos-1] != '\\' )
				parenths++;
			else if ( line[inPos] == '\)' && line[inPos-1] != '\\' )
				parenths--;
			if ( line[inPos] == '\{' && line[inPos-1] != '\\' )
				braces++;
			else if ( line[inPos] == '\}' && line[inPos-1] != '\\' )
				braces--;
			if ( line[inPos] == '\[' && line[inPos-1] != '\\' )
				brackets++;
			else if ( line[inPos] == '\]' && line[inPos-1] != '\\' )
				brackets--;
			if ( line[inPos] == '\'' && line[inPos-1] != '\\' )
				singleq++;
			else if ( line[inPos] == '\"' && line[inPos-1] != '\\' )
				doubleq++;
		}

		inPos++;
	}

	printf("\nparenthesis  : %d", parenths);
	printf("\nbraces       : %d", braces);
	printf("\nbrackets     : %d", brackets);
	printf("\nsingle quotes: %d", singleq % 2);
	printf("\ndouble quotes: %d", doubleq % 2);
	printf("\ncomments     : %d\n", comState);
}