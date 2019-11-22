#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
int numeric = 0, rev = 0, dir = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void reverse(char *lineptr[], int nlines);

void qsort2(void *lineptr[], int left, int right,
						int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int strCmpNoCase(char *s1, char *s2);
int strCmp2(char *s1, char *s2);

int main(int argc, char *argv[])
{
	int nlines, c;

	int (*comp2)(void *, void *);

	comp2 = &strCmp2;

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				rev = 1;
				break;
			case 'f':
				comp2 = &strCmpNoCase;
				break;
			case 'd':
				dir = 1;
				break;
			default:
				printf ("error: illegal option -%c\n",c);
				break;
			}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort2((void **) lineptr, 0, nlines-1,
				(int (*)(void*, void*))
				(numeric ? numcmp : comp2));
		if (rev)
			reverse(lineptr, nlines);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

void qsort2(void *v[], int left, int right,
						int (*comp)(void *, void*))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort2(v, left, last-1, comp);
	qsort2(v, last+1, right, comp);
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	else
		return 0;
}

int strCmpNoCase(char *s1, char *s2)
{
	for ( ; toupper(*s1) == toupper(*s2) || dir == 1 ; s1++, s2++){
		if (*s1 == '\0')
			return 0;

		if (dir == 1){
			if ((*s1 != ' ') && (!isalnum(*s1)))
				s1++;
			if ((*s2 != ' ') && (!isalnum(*s2)))
				s2++;
		}
	}

	return toupper(*s1) - toupper(*s2);
}

int strCmp2(char *s1, char *s2)
{
	for ( ; *s1 == *s2 || dir == 1 ; s1++, s2++){
		if (*s1 == '\0')
			return 0;

		if (dir == 1){
			if ((*s1 != ' ') && (!isalnum(*s1)))
				s1++;
			if ((*s2 != ' ') && (!isalnum(*s2)))
				s2++;
		}
	}

	return *s1 - *s2;
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int getline(char *line, int maxlen);
char *alloc(int size);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			if (strcmp (p,"xxxx") == 0)
				return nlines;
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
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

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int size)
{
	if (allocbuf + ALLOCSIZE - allocp >= size) {
		allocp += size;
		return allocp - size;
	} else
		return 0;
}

void reverse(char *lineptr[], int nlines)
{
	static int end = 0;
	static int start = 0;

	char *tmp;

	if (end == 0)
		end = nlines-1;

	tmp = lineptr[start];
	lineptr[start] = lineptr[end];
	lineptr[end] = tmp;

	start++;
	end--;

	if (end > start)
		reverse(lineptr,nlines-2);
}

