/*
 * Filename:	getint.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/01/2015
 *
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as
 * a valid representation of zero. Fix it to push such a character
 * back on the input.
 */

#include <stdio.h>
#include <ctype.h>

int getint(int *);
int getch(void);
void ungetch(int);

int main(void) {
	int c, n;
	while ((c = getint(&n)) != EOF) {
		if (c)
			printf("%d\n", n);
		else
			printf("input error\n");
	}
	return 0;
}

int getint(int *pn) {
	int c, sign;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* nan */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		int pom = c;
		c = getch();
		if (!isdigit(c)) {
			ungetch(pom);
			ungetch(c);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

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
