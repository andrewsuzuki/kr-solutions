/*
 * Filename:	indexer.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/09/2015
 *
 * Exercise 6-3. Write a cross-referencer that prints a list of all words in
 * a document, and, for each word, a list of the line numbers on which it
 * occurs. Remove noise words like "the," "and," and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD	100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

struct tnode {
	char *word; /* word */
	struct tlinen *linen; /* associated line number */
	struct tnode *left;
	struct tnode *right;
};

struct tlinen {
	int line;
	struct tlinen *next;
};

int cline = 1;

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
struct tlinen *lalloc(void);
char *_strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	struct tlinen *nln;

	if (p == NULL) {
		p = talloc();
		p->word = _strdup(w);
		p->left = p->right = NULL;

		p->linen = lalloc();
		p->linen->line = cline;
		p->linen->next = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		for (nln = p->linen; nln != NULL && nln->line != cline; nln = nln->next);
		if (nln == NULL) {
			nln = lalloc();
			nln->line = cline;
			nln->next = p->linen;
			p->linen = nln;
		}
	} else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	struct tlinen *nln;

	if (p != NULL) {
		treeprint(p->left);
		printf("%s: ", p->word);
		for (nln = p->linen; nln != NULL; nln = nln->next)
			printf("%d ", nln->line);
		printf("\n\n");
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* lalloc: make a tlinen */
struct tlinen *lalloc(void)
{
	return (struct tlinen *) malloc(sizeof(struct tlinen));
}

/* strdup: make a duplicate of s */
char *_strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

int getch(void);
void ungetch(int);
int getch_alt(void);

int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch_alt()));

	if (c == EOF) return EOF;

	*w++ = c;
	
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch_alt()) && *w != '_') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';

	return word[0];
}

int getch_alt(void) {
	int c;
	static int lc = -1;

	c = getch();

	if (c == EOF) return EOF; 

	if (lc == '/' && c == '*') {
		/* skip to end of comment */
		while ((c = getch())) {
			if (c == EOF) return EOF;
			if (lc == '*' && c == '/') break;
			lc = c;
		}
	}

	if (c == '"' && lc != '\\') {
		/* skip to end of quote */
		while ((c = getch())) {
			if (c == EOF) return EOF;
			if (c == '"' && lc != '\\') break;
			lc = c;
		}
	}

	if (c == '#') {
		/* skip to end of line */
		while ((c = getch()) != '\n')
			if (c == EOF) return EOF;
	}

	lc = c;
	return c;
}

#define BUFSIZE 1000

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { /* get a (possibly pushed back) character */
	int c = (bufp > 0) ? buf[--bufp] : getchar();
	if (c == '\n')
		cline++;
	return c;
}

void ungetch(int c) { /* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		if (c == '\n')
			cline--;
		buf[bufp++] = c;
	}
}