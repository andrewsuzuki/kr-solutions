/*
 * Filename:	print-whitespace.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

int main(void) {
	int c, spaces, tabs, newlines;

	spaces = tabs = newlines = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ')
			spaces++;
		else if (c == '\t')
			tabs++;
		else if (c == '\n')
			newlines++;
	}

	printf("Spaces: %d\n", spaces);
	printf("Tabs: %d\n", tabs);
	printf("Newlines: %d\n", newlines);

	return 0;
}
