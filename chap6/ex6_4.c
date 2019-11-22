#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD		100
#define LISTLIMIT	2000

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct indWords {
	int count;
	struct tnode *word;
} wordList[LISTLIMIT];

int wordCnt=0;

struct tnode *addtree(struct tnode *p, char *w);
void treeToArray(struct tnode *p);
void qsort2(struct indWords *wordList, int left, int right);
int getword(char *word, int lim);

main()
{
	struct tnode *root;
	char word[MAXWORD];
	int j;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	treeToArray(root);
	qsort2(wordList, 0, wordCnt-1);
	for (j = wordCnt-1; j >= 0; j--)
		printf("%4d %s\n", wordList[j].count, wordList[j].word->word);
	printf("Total number of words: %d\n", wordCnt);
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
		wordCnt++;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
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

void treeToArray(struct tnode *p)
{
	static j = 0;

	if (p != NULL) {
		treeToArray(p->left);
		wordList[j].count = p->count;
		wordList[j].word = p;
		j++;
		treeToArray(p->right);
	}
}

void swap(struct indWords *wordList, int i, int j);

void qsort2(struct indWords *wordList, int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	swap(wordList, left, (left + right) /2);
	last = left;
	for (i = left+1; i <=right; i++)
		if (wordList[i].count < wordList[left].count)
			swap(wordList, ++last, i);
	swap(wordList, left, last);
	qsort2(wordList, left, last-1);
	qsort2(wordList, last+1, right);
}
	
void swap(struct indWords *wordList, int i, int j)
{
	int tmpCount;
	struct tnode *tmpWord;

	tmpCount = wordList[i].count;
	tmpWord = wordList[i].word;
	wordList[i].count = wordList[j].count;
	wordList[i].word = wordList[j].word;
	wordList[j].count = tmpCount;
	wordList[j].word = tmpWord;
}

int getch(void);
void ungetch(int c);

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while(isspace(c = getch()))
		;

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

