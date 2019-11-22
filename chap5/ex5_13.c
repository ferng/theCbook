#include <stdio.h>
#include <string.h>

#define MAXLINES	5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

int main(int argc, char *argv[])
{
	int nlines, tailLines;

	if (argc == 1)
		tailLines = 10;
	else
		if (!(tailLines = atoi(argv[1]))){
			printf ("error: usage: prog {num of lines}\n");
			return 0;
		}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
		printf("\n");
		writelines(lineptr + (nlines - tailLines), tailLines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000
int getline(char *line, int maxline);
char *alloc(int size);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;

	while (nlines-- >0)
		printf("%s\n", *lineptr++);
}

void swap(char *v[], int i, int j);

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

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n){
		allocp += n;
		return allocp - n;
	} else
		return 0;
}
