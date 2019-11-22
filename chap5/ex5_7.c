#include <stdio.h>
#include <string.h>

#define MAXLINES	50

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines, char *storage);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

main()
{
	int nlines;
	char bigString[10000];

	if ((nlines = readlines(lineptr, MAXLINES, bigString)) >= 0){
		qsort(lineptr, 0, nlines-1);
		printf("\n");
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 50
int getline(char *line, int maxline);
char *alloc(int size);

int readlines(char *lineptr[], int maxlines, char *storage)
{
	int len, nlines;
	char *p, line[MAXLEN];

	p=storage;

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p+=MAXLEN;
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

void qsort(char *lineptr[], int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	swap(lineptr, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(lineptr[i], lineptr[left]) < 0)
			swap(lineptr, ++last, i);
	swap(lineptr, left, last);
	qsort(lineptr, left, last - 1);
	qsort(lineptr, last + 1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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
