#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
int numeric = 0, rev = 0, dir = 0, keys = 0, nums = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void reverse(char *lineptr[], int start, int end);

void qsort2(void *lineptr[], int left, int right, int col, int fields[],
						int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int strCmpNoCase(char *s1, char *s2);
int strCmp2(char *s1, char *s2);
void pullField(char *toScan, int curCol, char *field);

int main(int argc, char *argv[])
{
	int nlines, c, col=-1, fields[9], foundArgs, start, end, same;
	char startField[MAXLEN], endField[MAXLEN];

	int (*comp2)(void *, void *);

	comp2 = &strCmp2;

	fields[0] = 999;

	foundArgs = (argc == 1)?0:1;

	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		printf("error: input too big to sort\n");
		return 1;
	}
	while ((--argc > 0 && (*++argv)[0] == '-') || (!foundArgs)){
		while ((c = *++argv[0]) || !foundArgs){
			if(!foundArgs){
				c = ' ';
				*++argv[0];
			}
			switch (c) {
			case ' ':
				break;
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
			case 'k':
				numeric = rev = dir = 0;
				keys = 1;
				break;
			case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				if (keys == 0){
					printf ("error: illegal option -%c\n",c);
					return 1;
				} 
				else {
					if (nums == 1){
						printf ("error: illegal option -%c\n",c);
						return 1;
					}
					nums = 1;
					fields[++col] = (c - '0') - 1;
				}
				break;
			default:
				printf ("error: illegal option -%c\n",c);
				return 1;
			}
		foundArgs = 1;
		}

		if (keys == 1 && nums == 0){
			printf ("error: sorting by keys but no keys found");
			return 1;
		}

		start = 0;
		while (lineptr[start]){
			if (!keys){
				end = nlines - 1;
				col = 0;
				fields[col] = 0;
			}
			else if (col == 0){
				end = nlines - 1;
			}
			else {
				pullField(lineptr[start], fields[col-1], startField);
				same = 1;
				end = start;
				while (same) {
					if (! lineptr[end]) {
						end--;
						same = 0;
					}
					else {
						pullField(lineptr[end], fields[col-1], endField);
						if ((numeric ?  numcmp(startField, endField) :
										comp2(startField, endField)) == 0)
							end++;
						else {
							end--;
							same = 0;
						}
					}
				}
			}

			qsort2((void **) lineptr, start, end, (keys) ? col+1 : 0, fields,
						(int (*)(void*, void*))
						(numeric ? numcmp : comp2));
			if (rev)
				 reverse(lineptr, start, end); 
			nums = 0;

			start = end+1;
		}

		nums = 0;

	}
	printf("\n===========\n");
	writelines(lineptr, nlines);
	return 0;
}

void swap(void *v[], int i, int j);

void qsort2(void *v[], int left, int right, int col, int fields[],
						int (*comp)(void *, void*))
{
	int i, last, curCol;
	char str1[MAXLEN], str2[MAXLEN];

	curCol = (col) ? fields[col-1] : 0;

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++){
		pullField(v[i], curCol, str1);
		pullField(v[left], curCol, str2);
	
		if ((*comp)(str1, str2) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort2(v, left, last-1, col, fields, comp);
	qsort2(v, last+1, right, col, fields, comp);
}

void pullField(char *toScan, int curCol, char *field)
{

	int i, del = ' ';

	for (i = 1; i <= curCol; i++)
		while (*toScan++ != del && *toScan != '\0');

	while (*toScan != del && *toScan != '\0')
		*field++ = *toScan++;

	*field = '\0';
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
	while ((len = getline(line, MAXLEN)) > 1)
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
	}
	else
		return 0;
}

void reverse(char *lineptr[], int start, int end)
{
	char *tmp;

	tmp = lineptr[start];
	lineptr[start] = lineptr[end];
	lineptr[end] = tmp;

	start++;
	end--;

	if (end > start)
		reverse(lineptr, start, end);
}

