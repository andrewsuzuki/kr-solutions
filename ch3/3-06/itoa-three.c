/*
 * Filename:	itoa-three.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/29/2015
 *
 * Exercise 3-6. Write a version of itoa that accepts three arguments
 * instead of two. The third argument is a minimum field width;
 * the converted number must be padded with blanks on the left
 * if necessary to make it wide enough.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void itoa(int n, char string[], int width);
void reverse(char s[]);

int main(void) {
	char s[1000];

	itoa(0, s, 5);
	printf("%s\n", s);

	itoa(INT_MIN, s, 20);
	printf("%s\n", s);

	itoa(INT_MAX, s, 13);
	printf("%s\n", s);

	return 0;
}

/* itoa: convert n to characters in s,
 * now with min left padding */
void itoa(int n, char s[], int w) {
	int i, sign;

	sign = n;
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	while (i < w)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
