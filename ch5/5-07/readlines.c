/*
 * Filename:	readlines.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/03/2015
 *
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char linearr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

#define LA_SIZE 1000

int main()
{
	int nlines;
	char linearr[LA_SIZE];
	
	if ((nlines = readlines(lineptr, linearr, MAXLINES)) >= 0) {
		qsort (lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf ("error: input too big to sort\n");
		return 1;
	}
}
	
#define MAXLEN 1000
int _getline(char *, int);

int readlines(char *lineptr[], char linearr[], int maxlines)
{
	int nlines, len;
	char *bufp;
	char line[MAXLEN];

	nlines = 0;
	bufp = linearr;
	
	while ((len = _getline(line, MAXLEN)) > 0){
		if (linearr + LA_SIZE - bufp < len)
			return -1;
		line[len - 1] = '\0';
		strcpy(bufp, line);
		lineptr[nlines++] = bufp;
		bufp += len;
	}

	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;
	
	for (i = 0; i < nlines; ++i)
		printf ("%s\n", lineptr[i]);
}

int _getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap (v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap (v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap (char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}