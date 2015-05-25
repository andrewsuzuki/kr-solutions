/*
 * Filename:	linefold.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/24/2015
 *
 * Exercise 1-22. Write a program to ``fold'' long input lines into two
 * or more shorter lines after the last non-blank character that occurs
 * before the n-th column of input. Make sure your program does
 * something intelligent with very long lines, and if there are no
 * blanks or tabs before the specified column.
 *
 * *** Words longer than line width aren't wrapping too nicely, look into this.
 */

#include <stdio.h>

#define TAB_COLS	8
#define LINE_WIDTH	16
#define TRUE		1
#define FALSE		0

int main(void) {
	int c, i, linepos, len, lwl[LINE_WIDTH];

	len = linepos = 0;
	
	for (i = 0; i < LINE_WIDTH; ++i)
		lwl[i] = 0;

	printf("0123456789ABCDEF\n");

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			for (i = 0; i < len; ++i) {
				putchar(lwl[i]);
				lwl[i] = 0;
			}
			len = 0;
			linepos = 0;
			putchar('\n');
			continue;
		}

		if (linepos == LINE_WIDTH) {
			/* current character is past last stop */
			if (c != '\t' && c != ' ')
				putchar('\n'); /* word continues, so don't complete line */

			linepos = 0;

			/* if we were saving instead of printing,
			 * print what we saved so far */
			for (i = 0; i < len; ++i) {
				if (c != '\t' && c != ' ')
					++linepos;
				putchar(lwl[i]);
				lwl[i] = 0;
			}
			len = 0;

			if (c == '\t' || c == ' ' || linepos == LINE_WIDTH) {
				putchar('*');
				putchar('\n');
				linepos = 0;
			}
		}

		if (c == '\t') {
			/* count characters left until
			 * right before next tab stop */
			for (i = 0; (i + linepos) % TAB_COLS != 0; ++i);
			linepos += i - 1;
		}

		if (c == '\t' || c == ' ') {
			for (i = 0; i < len; ++i) {
				putchar(lwl[i]);
				lwl[i] = 0;
			}
			len = 0;
			putchar(c);
		} else {
			++len;
			lwl[len - 1] = c;
		}

		++linepos;
	}

	for (i = 0; i < len; ++i) {
		putchar(lwl[i]);
		lwl[i] = 0;
	}

	putchar('\n');

	return 0;
}
