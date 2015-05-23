/*
 * Filename:	freq-hist.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercise 1-14. Write a program to print a histogram of
 * the frequencies of different characters in its input.
 */

#include <stdio.h>

int main(void) {
	int c, i, j;
	int nfreq[256];

	for (i = 0; i < 256; i++)
		nfreq[i] = 0;

	while ((c = getchar()) != EOF)
		nfreq[c]++;

	for (i = 0; i < 256; i++) {
		if (nfreq[i] == 0)
			continue;

		if (i == '\n')
			printf("\\n");
		else if (i == '\b')
			printf("\\b");
		else if (i == '\t')
			printf("\\t");
		else if (i == ' ')
			printf("[space]");
		else
			putchar(i);

		putchar('\t');

		for (j = nfreq[i]; j > 0; j--)
			putchar('=');

		putchar('\n');
	}

	return 0;
}
