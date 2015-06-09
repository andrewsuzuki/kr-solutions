/*
 * Filename: listfreq.c
 * Author:	 Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	 06/09/2015
 *
 * Exercise 6-4. Write a program that prints the distinct words
 * in its input sorted into decreaseing order of frequency of
 * occurrence. Precede each word by its count.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD		100
#define MAXWORDS	5000

struct tnode *addtree(struct tnode *, char *);
void linearize(struct tnode *p, struct tnode *m[], int *i);
int compare(const void *p1, const void *p2);
void treeprint(struct tnode *);
void linearprint(struct tnode *m[], int size);
int getword(char *, int);

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

int main(int argc, char *argv[])
{
	int i = 0;
	struct tnode *root;
	struct tnode *nodelist[MAXWORDS];
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	linearize(root, nodelist, &i);
	qsort(nodelist, i, sizeof (struct tnode *), compare);
	linearprint(nodelist, i);
	return 0;
}

struct tnode *talloc(void);
char *_strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = _strdup(w);
		p->count = 1;

		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
	} else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}

void linearize(struct tnode *p, struct tnode *m[], int *i)
{
	if (p != NULL) {
		m[(*i)++] = p;
		linearize(p->left, m, i);
		linearize(p->right, m, i);
	}
}

int compare(const void *p1, const void *p2)
{
    return (*(struct tnode **)p2)->count - (*(struct tnode **)p1)->count;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

void linearprint(struct tnode *m[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%4d %s\n", m[i]->count, m[i]->word);
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
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

int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch()));

	if (c == EOF) return EOF;

	*w++ = c;
	
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';

	return word[0];
}

#define BUFSIZE 1000

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { /* get a (possibly pushed back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		buf[bufp++] = c;
	}
}