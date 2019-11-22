#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE		101
#define MAXWORD			100

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct	nlist *hashtab[HASHSIZE];

unsigned int hash (char *s);
int getword(char *word, int lim);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int undef(char *s);
char *strdup2(char *s);

main()
{
	char word[MAXWORD], defn[MAXWORD];
	struct nlist *np;

	while(1 == 1){
		if (getword(word, MAXWORD) == EOF)
			break;
		else if (!strcmp(word, "#")){
			if (getword(word, MAXWORD) == EOF)
				break;
			else if (!strcmp(word, "define")){
				if (getword(word, MAXWORD) == EOF && isalpha(word[0]))
					break;
				else{
					if (getword(defn, MAXWORD) == EOF && isalnum(word[0]))
						break;
					else{
						printf("installed: %s, %s\n", word, defn);
						install(word, defn);
					}
				}
			}
		}
	}	

	if ((np = lookup("THIRD")) == NULL) 
		printf("THIRD: name not found\n");
	else
		printf("%s, %s\n", np->name, np->defn);

	if (undef("THIRD") == 1)
		printf("THIRD: removed\n");

	if ((np = lookup("CORRECT")) == NULL) 
		printf("CORRECT: name not found\n");
	else
		printf("%s, %s\n", np->name, np->defn);

	if ((np = lookup("SECOND")) == NULL) 
		printf("SECOND: name not found\n");
	else
		printf("%s, %s\n", np->name, np->defn);

	if ((np = lookup("THIRD")) == NULL) 
		printf("THIRD: name not found\n");
	else
		printf("%s, %s\n", np->name, np->defn);

	if ((np = lookup("FOURTH")) == NULL) 
		printf("FOURTH: name not found\n");
	else
		printf("%s, %s\n", np->name, np->defn);

	if ((np = lookup("LAST")) == NULL) 
		printf("LAST: name not found\n");
	else
		printf("%s, %s\n", np->name, np->defn);
}

unsigned int hash (char *s)
{
	unsigned int hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE; 
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned int hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup2(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);

	if ((np->defn = strdup2(defn)) == NULL)
		return NULL;
	return np;
}

char *strdup2(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

int undef(char *s)
{
	struct nlist *np;
	struct nlist *prevNp = NULL;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next){
		if (strcmp(s, np->name) == 0){
			if (prevNp != NULL)
				prevNp->next = np->next;
			else
				hashtab[hash(s)] = NULL;
			free(np);
			return 1;
		}
		prevNp = np;
	}
	return 0;
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
	if (!isalnum(c)) {
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

