/*
 * Filename:	equivalent-for.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/25/2015
 *
 * Exercise 2-2. Write a loop equivalent to the for loop above
 * without using && or ||.
 */

#include <stdio.h>

#define MAX_CHARS 1000

int main(void) {
	int i, c;
	char s[MAX_CHARS];

	for (i = 0; i < MAX_CHARS - 1; ++i) {
		c = getchar();
		if (c == '\n') break;
		if (c == EOF) break;
		s[i] = c;
	}

	return 0;
}
