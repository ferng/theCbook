#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD		100

char decList[11][10] = {"signed", "unsigned", "long", "short", "int", "double",
												"char", "void", "float", "struct", ""};

struct tnode {
	char *word;
	char *key;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w, int compLen);
void treeprint(struct tnode *p);
int getword(char *word, int lim);

main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	int inDecl=0, w, i, compLen=6;

	if (argc > 1){
		if (!(compLen = -(atoi(argv[1])))){
			printf ("error: usage: prog {num of comparison chars\n");
			return 1;
		}
	}	

	root = NULL;

	while (1 == 1){
		while (2 == 2){
			if ((w = getword(word, MAXWORD)) == EOF)
				break;
			if (isalpha(word[0])){
				for (i = 0;
							(decList[i][0] != '\0') && !(strcmp(word, decList[i]) == 0);
							i++);			/* let's look for word in declaration list */
				if (decList[i][0] != '\0'){				/* we found it */
					inDecl = 1;
					continue;
				} else if (inDecl == 1)						/* didn't find it */
					break;
			} else if (word[0] == ')' || word[0] == ';')
				inDecl = 0;
		}
		if (w == EOF)
			break;
		root = addtree(root, word, compLen);
	}

	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *strdup2(char *s, int compLen);

struct tnode *addtree(struct tnode *p, char *w, int compLen)
{
	int i, cond;
	char tmpW[MAXWORD];

	for (i = 0; i < compLen ; i++)
		tmpW[i] = w[i];
	tmpW[i] = '\0';

	if (p == NULL) {
		p = talloc();
		p->word = strdup2(w, 0);
		p->key = strdup2(w, compLen);
		printf("debug: addtree: %s\n", p->key);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(tmpW, p->key)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w, compLen);
	else
		p->right = addtree(p->right, w, compLen);
	return p;
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup2(char *s, int compLen)
{
	char *p;
	int i;

	if (compLen == 0){
		p = (char *) malloc(strlen(s)+1);
		if (p != NULL)
			strcpy(p, s);
	} else {
		p = (char *) malloc(compLen+1);
		if (p != NULL){
			for (i = 0; i < compLen ; i++)
				p[i] = s[i];
			p[i] = '\0';
		}
	}

	return p;
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->key);
		treeprint(p->right);
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
		;

	if (c != EOF)
		*w++ = c;

	if (c == '/'){
		c = getch();
		if (c != '*')
			ungetch(c);
		else																	/* we're in a comment */
			for ( ; --lim > 0;){
				if ((c = getch()) == '*'){
					if ((c = getch()) == '/')
						return c;									
					else{
						ungetch(c);
						lim++;
					}
				}
			}							
	} else if (c == '"') {
		while ((c = getch()) != '"')
			;
	} else if (!isalpha(c)) {
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

