/*
 * Filename:	tail.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/06/2015
 *
 * Exercise 5-13. Write the program tail, which prints the last n lines
 * of its input. By default, n is 10, let us say, but it can be changed
 * by an optional argument, so that
 * 		tail -n
 * prints the last n lines. The program should behave rationally no matter
 * how unreasonable the input or the value of n. Write the program so it
 * makes the best use of available storage; lines should be stored as
 * in the sorting program of Section 5.6, no in a two-dimensional
 * array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N 	10
#define MAXLINES 	5000
#define MAXLEN  	1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char linearr[], int nlines);
void writelines(char *lineptr[], int nlines, int nstart);

int main(int argc, char *argv[]) {
	int i, nlines, n;
	char linearr[MAXLEN];

	n = 0;

	for (i = 1; i < argc; i++)
		if (*argv[i] == '-')
			n = atoi(argv[i] + 1);

	if (n <= 0) {
		printf("error: must supply -n greater than zero\n");
		return 1;
	}

	if ((nlines = readlines(lineptr, linearr, MAXLINES)) >= 0) {
		writelines(lineptr, nlines, (nlines > n) ? (nlines - n) : 0);
		return 0;
	} else {
		printf("error: input too big\n");
		return 1;
	}
}
	
int _getline(char *, int);

int readlines(char *lineptr[], char linearr[], int maxlines) {
	int nlines, len;
	char *bufp;
	char line[MAXLEN];

	nlines = 0;
	bufp = linearr;
	
	while ((len = _getline(line, MAXLEN)) > 0){
		if (linearr + MAXLEN - bufp < len)
			return -1;
		line[len - 1] = '\0';
		strcpy(bufp, line);
		lineptr[nlines++] = bufp;
		bufp += len;
	}

	return nlines;
}

void writelines(char *lineptr[], int nlines, int nstart) {
	int i;
	for (i = nstart; i < nlines; ++i)
		printf("%s\n", lineptr[i]);
}

int _getline(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}