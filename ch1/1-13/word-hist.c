/*
 * Filename:	word-hist.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercise 1-13. Write a program to print a histogram of the lengths
 * of words in its input. It is easy to draw the histogram with the
 * bars horizontal; a vertical orientation is more challenging.
 */

#include <stdio.h>

int main(void) {
	int c, i, j, wc;
	int nlen[20];

	for (i = 0; i < 20; i++)
		nlen[i] = 0;

	wc = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			nlen[wc]++;
			wc = 0;
		} else {
			wc++;
		}
	}

	for (i = 0; i < 20; i++) {
		printf("%d chars:\t", i);
		for (j = nlen[i]; j > 0; j--)
			putchar('=');
		putchar('\n');
	}

	return 0;
}
