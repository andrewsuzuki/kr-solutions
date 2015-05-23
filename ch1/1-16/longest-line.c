/*
 * Filename:	longest-line.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/23/2015
 *
 * Exercise 1-16. Revise the main routine of the longest-line program
 * so it will correctly print the length of arbitrary long input
 * lines, and as much as possible of the text.
 */

#include <stdio.h>

#define MAXLINE	5

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void) {
	int len;
	int llen;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];
	char start[MAXLINE];

	llen = max = 0;
	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (llen + len > max) {
			max = llen + len;
			if (llen)
				copy(longest, start);
			else
				copy(longest, line);
		}

		if (line[len-1] != '\n') {
			if (llen == 0)
				copy(start, line);
			llen += len;
		} else {
			llen = 0;
		}
	}

	if (max > 0) {
		printf("%s", longest);
		if (longest[max-1] != '\n') {
			putchar('\n');
		}
		printf("Characters: %d\n", max);
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
