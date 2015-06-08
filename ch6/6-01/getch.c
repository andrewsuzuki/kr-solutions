/*
 * Filename:	getch.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 *
 * Getch/ungetch common header
 */

#include <stdio.h>
#include "getch.h"

#define BUFSIZE 1000

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { /* get a (possibly pushed back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}