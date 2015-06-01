/*
 * Filename:	itoa-recursive.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/01/2015
 *
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an interger into a string by calling a recursive routine.
 */

#include <stdio.h>

#define MAX_INT_STR 100

void itoa(int n, char string[]);
int itoa_s(int n, char string[], int index);

int main(void) {
	char s1[MAX_INT_STR];
	char s2[MAX_INT_STR];
	char s3[MAX_INT_STR];
	char s4[MAX_INT_STR];

	itoa(0, s1);
	printf("%s\n", s1);

	itoa(1, s2);
	printf("%s\n", s2);

	itoa(47, s3);
	printf("%s\n", s3);

	itoa(-47, s4);
	printf("%s\n", s4);

	return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
	int i = itoa_s(n, s, 0);
	s[i] = '\0';
}

/* itoa_s: a step of itoa */
int itoa_s(int n, char s[], int i) {
	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
	if (n / 10)
		i = itoa_s(n / 10, s, i);
	s[i++] = n % 10 + '0';
	return i;
}
