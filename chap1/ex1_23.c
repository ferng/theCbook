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
	int inPos, outPos, comState, strState;

	char outLine[MAXLEN];

	inPos = outPos = 0;
	comState = strState = OUT;

	while (line[inPos] != '\0'){

		if (line[inPos] == '/' && line[inPos+1] == '*' && strState == OUT)
			comState = IN;

		if (line[inPos] == '*' && line[inPos+1] == '/' && strState == OUT){
			inPos += 2;
			comState = OUT;
		}

		if (line[inPos] == '"' && comState == OUT)
			if (strState == IN)
				strState = OUT;
			else
				strState = IN;

		if (comState == OUT)
			outLine[outPos++] = line[inPos];

		inPos++;
	}

	outLine[outPos] = '\0';
	printf("%s", outLine);
}