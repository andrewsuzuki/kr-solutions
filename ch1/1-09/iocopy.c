/*
 * Filename:	iocopy.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercise 1-9. Write a program to copy its input to its output,
 * replacing each string of one or more blanks by a single blank.
 */

#include <stdio.h>

int main(void) {
	int c, lc;

	while ((c = getchar()) != EOF) {
		if (c != ' ' || lc != ' ')
			putchar(c);

		lc = c;
	}

	return 0;
}
