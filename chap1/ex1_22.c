#include <stdio.h>

#define	RIGHTMAX		48
#define	RIGHTBREAK	42
#define	MAXLEN			300

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
	int inPos, outPos;

	char outLine[MAXLEN];

	inPos = outPos = 0;

	while (line[inPos] != '\0'){
		if (outPos == RIGHTMAX){
			outLine[outPos] = '-';
			outLine[++outPos] = '\n';
			outLine[++outPos] = '\0';
			printf("%s", outLine);
			outPos = 0;
		}
		else if (line[inPos] == ' ' && outPos >= RIGHTBREAK){
			outLine[outPos] = '\n';
			outLine[++outPos] = '\0';
			printf("%s", outLine);
			outPos = 0;
		}
		else
			outLine[outPos++] = line[inPos++];
	}

	outLine[outPos] = '\0';
	printf("%s", outLine);
}