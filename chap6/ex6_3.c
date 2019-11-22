#include <stdio.h>  
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD		100
#define MAXFINDS	2000

struct tnode {
	char *word;
	int count;
	int key;
	struct tnode *left;
	struct tnode *right;
};

struct fLines {
	int key;
	int line;
} lineList[MAXFINDS];

int wordCnt=0, curFound=0, curLine=1;

char ignore[11][10] = {"a", "that", "the", "in", "of", "by", "this", "an", "to",
											"or", ""};

struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p, struct fLines *pLineList);
void qsort2(struct fLines *pLineList, int left, int right);
int getword(char *word, int lim);

main()
{
	struct tnode *root;
	char word[MAXWORD];
	int i;

	root = NULL;
	while ((getword(word, MAXWORD) != EOF) && curFound < MAXFINDS)
		if (isalpha(word[0])){
			for (i = 0;
						(ignore[i][0] != '\0') && !(strcmp(word,ignore[i]) == 0); 
						i++);
			if (ignore[i][0] == '\0') /* it's not one of the words to exclude */ 
				root = addtree(root, word);
		}

	qsort2(lineList, 0, curFound-1); 
	treeprint(root, lineList); 
	printf("Total number of words and keys: %d, %d\n", wordCnt, curFound);
	return 0;
}

struct tnode *talloc(void);
char *strdup2(char *s);

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup2(w);
		p->count = 1;
		p->left = p->right = NULL;
		p->key = wordCnt;
		lineList[curFound].key = wordCnt; 
		lineList[curFound].line = curLine;
		wordCnt++;
		curFound++;
	} else if ((cond = strcmp(w, p->word)) == 0){
		p->count++;
		lineList[curFound].key = p->key; 
		lineList[curFound].line = curLine;
		curFound++;
	} else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	lineList[curFound+1].key = -1; 
	return p;
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup2(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

void swap(struct fLines *pLineList, int i, int j);

void qsort2(struct fLines *pLineList, int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	swap(pLineList, left, (left + right) /2);
	last = left;
	for (i = left+1; i <=right; i++)
		if (pLineList[i].key < pLineList[left].key)
			swap(pLineList, ++last, i);
	swap(pLineList, left, last);
	qsort2(pLineList, left, last-1);
	qsort2(pLineList, last+1, right);
}
	
void swap(struct fLines *pLineList, int i, int j)
{
	int tmpKey, tmpLine;

	tmpKey = pLineList[i].key;
	tmpLine = pLineList[i].line;
	pLineList[i].key = pLineList[j].key;
	pLineList[i].line = pLineList[j].line;
	pLineList[j].key = tmpKey;
	pLineList[j].line = tmpLine;
}

void treeprint(struct tnode *p, struct fLines *pLineList)
{
	int i;

	if (p != NULL) {
		treeprint(p->left, pLineList);
		printf("%4d %s: ", p->count, p->word); 
		for	(i = 0; pLineList[i].key >= 0 && pLineList[i].key <= p->key; i++) 
			if (pLineList[i].key == p->key)
				printf ("%d, ",pLineList[i].line);
		printf("\n");
		treeprint(p->right, pLineList);
	}
}

int getch(void);
void ungetch(int c);

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while(isspace(c = getch()))
		if (c == '\n'){
			curLine++;
		}

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("error: ungetch: too many chars\n");
	else
		buf[bufp++] = c;
}

