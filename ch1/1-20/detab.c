/*
 * Filename:	detab.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/23/2015
 *
 * Exercise 1-20. Write a program detab that replaces tabs in the input
 * with the proper number of blanks to space to the next tab stop. Assume
 * a fixed set of tab stops, say every n columns. Should n be a variable
 * or a symbolic parameter?
 */

#include <stdio.h>

#define TAB_COLS 8

int left_in_col(int linepos);

int main(void) {
	int c, i, linepos;

	linepos = -1;
	while ((c = getchar()) != EOF) {
		linepos++;

		if (c == '\n') {
			linepos = -1;
		} else if (c == '\t') {
			i = left_in_col(linepos);
			if (!i) i = TAB_COLS; /* tab landed on tab stop */
			linepos += i - 1; /* fake new line position */
			for (; i > 0; --i)
				putchar(' '); /* write space until stop */
			continue;
		}

		putchar(c);
	}

	return 0;
}

/* left_in_col: given current line position (after \n),
 * return number of characters left until next tab stop */
int left_in_col(int linepos) {
	int col;
	for (col = 0; col * TAB_COLS <= linepos; ++col);
	return (col * TAB_COLS) - linepos;
}
