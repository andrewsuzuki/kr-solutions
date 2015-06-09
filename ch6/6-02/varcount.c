/*
 * Filename:	varcount.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/08/2015
 *
 * Exercise 6-2. Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical
 * in the first 6 characters, but different somewhere thereafter.
 * Don't count words within strings and comments. Make 6 a
 * parameter that can be set from the command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getch.h"

#define DEFAULT_FIRST_N	6
#define MAXWORD			100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

struct tnode {
	char *stub; /* stub (prefix) of the associated group */
	struct tgroup *group; /* associated group */
	struct tnode *left;
	struct tnode *right;
};

struct tgroup {
	char *word;
	struct tgroup *next;
};

int firstn = DEFAULT_FIRST_N;

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	if (argc > 1 && *argv[1] == '-')
		if ((firstn = atoi(argv[1] + 1)) < 1)
			firstn = DEFAULT_FIRST_N;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
struct tgroup *galloc(void);
char *_strdup(char *, int);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	struct tgroup *newgroup;

	if (p == NULL) {
		p = talloc();
		p->stub = _strdup(w, firstn);
		p->left = p->right = NULL;

		p->group = galloc();
		p->group->word = _strdup(w, -1);
		p->group->next = NULL;
	} else if ((cond = strncmp(w, p->stub, firstn)) == 0) {
		for (newgroup = p->group; newgroup != NULL && strcmp(newgroup->word, w); newgroup = newgroup->next);
		if (newgroup == NULL) {
			newgroup = galloc();
			newgroup->word = _strdup(w, -1);
			newgroup->next = p->group;
			p->group = newgroup;
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
	struct tgroup *tmp_group;

	if (p != NULL) {
		treeprint(p->left);
		printf("Group %s:\t", p->stub);
		for (tmp_group = p->group; tmp_group != NULL; tmp_group = tmp_group->next)
			printf("%s ", tmp_group->word);
		printf("\n");
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* galloc: make a tgroup */
struct tgroup *galloc(void)
{
	return (struct tgroup *) malloc(sizeof(struct tgroup));
}

/* strdup: make a duplicate of s */
char *_strdup(char *s, int n)
{
	char *p;
	int len = strlen(s);
	if (n > 0 && len > n)
		len = n;

	p = (char *) malloc(len + 1);
	if (p != NULL)
		strncpy(p, s, len);
	return p;
}

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