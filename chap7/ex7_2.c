#include <stdio.h>
#include <string.h>

#define	MAXLENIN			300
#define	MAXLENOUT			400
#define	RIGHTBREAK		42
#define	RIGHTMAX			48

int getline(char *line, int maxlen);
void parseLine(char *lineIn, char *lineOut);
void procLine(char *lineIn);

main()
{
	int len;
	char lineIn[MAXLENIN];
	char lineOut[MAXLENOUT];

	while ((len = getline(lineIn, MAXLENIN)) > 0){
		parseLine(lineIn, lineOut); 
		procLine(lineOut);
	}
	return 0;
}

int getline(char *s, int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		*s++ = c;
	if (c == '\n') {
		*s++ = c;
		++i;
	}
	*s++ = '\0';

	return i;
}

void parseLine(char *lineIn, char *lineOut)
{
	int i=0, outPos=0;
	char c, tmp[5];

	while ((c=lineIn[i++]) != '\0'){
		if (isprint(c))
			lineOut[outPos++] = c;
		else{
			sprintf(tmp, "[%x]", c);
			strcat(lineOut, tmp);
			outPos += strlen(tmp);
		}
		lineOut[outPos] = '\0';
	}
	lineOut[outPos] = '\0';
}

void procLine(char *line)
{
	int inPos, outPos;
	char outLine[MAXLENOUT];

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
	printf("%s\n", outLine);
}
