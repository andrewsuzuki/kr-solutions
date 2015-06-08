/*
 * Filename:	getword.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/01/2015
 *
 * Exercise 6-1. Our version of getword does not properly handle
 * underscores, string constants, comments, or preprocessor
 * control lines. Write a better version.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "getch.h"

#define MAXWORD 100

#define NKEYS (sizeof keytab / sizeof(struct key))

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"define", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0,
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

int in_comment = false;
int in_pre = false;

int main(void) {
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	}

	for (n = 0; n < NKEYS; n++)
		printf("%4d %s\n", keytab[n].count, keytab[n].word);

	return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else 
			return mid;
	}

	return -1;
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