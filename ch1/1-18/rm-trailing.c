/*
 * Filename:	rm-trailing.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/23/2015
 *
 * Exercise 1-18. Write a program to remove trailing blanks and tabs
 * from each line of input, and to delete entirely blank lines.
 */

#include <stdio.h>

#define TRUE	1
#define FALSE	0
#define MAXLINE	1000

int my_getline(char line[], int maxline);
int rm_tw(char line[], int length);

int main(void) {
	int len;
	char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		rm_tw(line, len);
		if (line[0] != '\n')
			printf("%s", line);
	}

	return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) {
	int c, i;

	for (i=0; i < lim-1 && (c=getchar()) != EOF && c!= '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* rm_tw: remove trailing whitespace (blanks and tabs), return new length */
int rm_tw(char s[], int len) {
	int nlr = FALSE;

	s[len] = 0; /* remove \0 */

	if (s[len-1] == '\n') {
		s[len-1] = 0;
		--len;
		nlr = TRUE;
	}

	for (; len > 0 && (s[len-1] == ' ' || s[len-1] == '\t'); --len)
		s[len-1] = 0;

	if (nlr == TRUE) {
		++len;
		s[len-1] = '\n';
	}

	s[len] = '\0';

	return len;
}
