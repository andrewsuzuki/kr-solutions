/*
 * Filename:	words-on-lines.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercise 1-12. Write a program that prints its input one word per line.
 */

#include <stdio.h>

int main(void) {
	int c, pc;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (pc == 0) putchar('\n');
			pc = 1;
		} else {
			putchar(c);
			pc = 0;
		}
	}

	return 0;
}
