/*
 * Filename:	sort-field.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/08/2015
 *
 * Exercise 5-17. Adda field-handling capability, so sorting may be done
 * on fields within lines, each field sorted according to an independent
 * set of options. (The index for this book was sorted with -df for the)
 * index category and -n for the page numbers).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int _strcmp(char *, char *);
int numcmp(char *, char *);

int order = 1;
int fold = false;
int directory = false;
int start = 0;
int end = 0;

int main(int argc, char *argv[]) {
	int i;
	int nlines;
	int numeric = false;

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0)
			numeric = true;
		else if (strcmp(argv[i], "-r") == 0)
			order = -1;
		else if (strcmp(argv[i], "-f") == 0)
			fold = true;
		else if (strcmp(argv[i], "-d") == 0)
			directory = true;
		else if (*argv[i] == '+' && (start = atoi(++argv[i])) < 0)
			start = -1;
		else if (*argv[i] == '-' && (end = atoi(++argv[i])) < 0)
			end = -1;
		else {
			printf("usage: sort -n -r -f -d +start -end\n");
			return 1;
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		_qsort((void **) lineptr, 0, nlines - 1,
			(int (*)(void *, void *))(numeric ? numcmp : _strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (order * (*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	_qsort(v, left, last - 1, comp);
	_qsort(v, left + 1, right, comp);
}

#include <stdlib.h>
void substr(char *s, char *t);

int numcmp(char *s1, char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int _strcmp(char *s1, char *s2)
{
	int i;

	s1 += start;
	s2 += start;

	if (directory) {
		while (!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
			s1++;
		while (!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
			s2++;
	}

	for (i = 0; i < (end - start) && fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2); i++) {
		if (*s1 == '\0')
			return 0;

		s1++;
		s2++;

		if (directory) {
			while (!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
				s1++;
			while (!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
				s2++;
		}
	}

	return fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
}

/* substr: copies part of *s to *t (specified by external start/end) */
void substr(char *s, char *t) {
	int i;
	int len = strlen(*s) - 1;
	int tstart = start;
	int tend = end;
	if (tstart > (len - 1))
		tstart = len - 1;
	if (tend > (len - 1))
		tend = len - 1;
	for (i = tstart; i <= tend; i++, t++)
		*t = s[i];
	*t = '\0';
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int _getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = _getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf ("%s\n", lineptr[i]);
}

int _getline(char s[], int limits)
{
    int i, c;
    for (i = 0; i < limits - 1 && (s[i] = getchar()) != EOF && s[i] != '\n'; i++);
    if (s[i] == '\n')
		i++;
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
    } else
		return 0;
}