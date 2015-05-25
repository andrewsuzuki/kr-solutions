/*
 * Filename:	remove-comments.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/25/2015
 *
 * Exercise 1-23. Write a program to remove all comments from
 * a C program. Don't forget to handle quoted strings and
 * character constants properly. C comments don't nest.
 */

#include <stdio.h>

#define TRUE	1
#define FALSE	0

int main(void) {
	int c, lc, stop, in_comment, in_quote;

	in_comment = in_quote = FALSE;
	stop = 0;
	lc = EOF;

	while ((c = getchar()) != EOF) {
		if (c == '/') {
			if (!in_quote && lc == '*') {
				in_comment = FALSE;
				stop = 2;
			}
		} else if (c == '*') {
			if (!in_quote && lc == '/') {
				in_comment = TRUE;
				stop = 2;
			}
		} else if (c == '"' && lc != '\\' && lc != '\'') {
			if (!in_comment) {
				if (in_quote)
					in_quote = FALSE;
				else
					in_quote = TRUE;
			}
		}

		if (!in_comment && !stop && lc != EOF)
			putchar(lc);
		else if (stop)
			stop--;

		lc = c;
	}

	if (!in_comment && !stop && lc != EOF)
		putchar(lc);

	return 0;
}
