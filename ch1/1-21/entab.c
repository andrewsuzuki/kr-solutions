/*
 * Filename:	entab.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/24/2015
 *
 * Exercise 1-21. Write a program entab that replaces strings of blanks
 * by the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab. When either a tab or a single blank
 * would suffice to reach a tab stop, which should be given preference?
 */

#include <stdio.h>

#define TAB_COLS 8

int left_in_col(int linepos);

int main(void) {
	int c, linepos, b, needed;

	linepos = -1;
	b = 0;

	while ((c = getchar()) != EOF) {
		linepos++;

		if (c == '\n') {
			linepos = -1;
		} else if (c == '\t') {
			linepos += left_in_col(linepos) - 1; /* fake the col */
		} else if (c == ' ') {
			b++;

			if (b == 1) {
				needed = left_in_col(linepos);
				if (!needed) needed = TAB_COLS;
			} else if (b == needed) {
				putchar('\t');
				b = 0;
				needed = 0;
			}

			continue;
		}

		if (b > 0) {
			/* didn't reach tab stop with blanks */
			for (; b > 0; --b)
				putchar(' ');
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
