/*
 * Filename:	reverse.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/23/2015
 *
 * Exercise 1-19. Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverses its input a line at a time.
 */

#include <stdio.h>

#define MAXLINE	1000

int my_getline(char line[], int maxline);
void reverse(char line[], int length);

int main(void) {
	int len;
	char line[MAXLINE];

	while ((len = my_getline(line, MAXLINE)) > 0) {
		reverse(line, len);
		putchar('\n');
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

void reverse(char s[], int lim) {
	int i = lim - 1;

	if (s[i] == '\n')
		--i;

	for (; i >= 0; --i)
		putchar(s[i]);
}
