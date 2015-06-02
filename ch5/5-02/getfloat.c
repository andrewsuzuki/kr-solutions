/*
 * Filename:	getfloat.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/01/2015
 *
 * Exercise 5-2. Write getfloat, the floating-point analog of getint.
 * What type does getfloat return as its function value?
 */

#include <stdio.h>
#include <ctype.h>

int getfloat(double *);
int getch(void);
void ungetch(int);

int main(void) {
	int c;
	double n;
	while ((c = getfloat(&n)) != EOF) {
		if (c)
			printf("%f\n", n);
		else
			printf("input error\n");
	}
	return 0;
}

int getfloat(double *pn) {
	int c, sign, e;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* nan */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');

	e = 0;

	if (c == '.')
		for (; isdigit((c = getch())); e--)
			*pn = 10.0 * *pn + (c - '0');

	if (c == 'e' || c == 'E') {
		int esign = 1;
		int exp = 0;
		c = getch();
		if (c == '+' || c == '-') {
			esign = (c == '-') ? -1 : 1;
			c = getch();
		}
		for (; isdigit(c); c = getch())
			exp = exp * 10 + (c - '0');
		e += exp * esign;
	}

	for(; e > 0; e--)
		*pn *= 10.0;

	for(; e < 0; e++)
		*pn /= 10.0;

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
