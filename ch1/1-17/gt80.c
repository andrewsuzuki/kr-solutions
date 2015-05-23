/*
 * Filename:	gt80.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/23/2015
 *
 * Exercise 1-17. Write a program to print all input lines
 * that are longer than 80 characters.
 */

#include <stdio.h>

#define MAXLINE	1000
#define MIN	80

int my_getline(char line[], int maxline);

int main(void) {
	int len;
	char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0)
		if (len > MIN) printf("%s", line);

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
