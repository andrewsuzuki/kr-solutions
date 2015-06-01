/*
 * Filename:	reverse-recursive.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/01/2015
 *
 * Exercise 4-13. Write a recursive version of the function reverse(s),
 * which reverses a string s in place.
 */

#include <stdio.h>

void reverse(char s[], int lim);
void reverse_i(char s[], int lim, int i);

int main(void) {
	char s1[] = "test";
	char s2[] = "abccba";
	char s3[] = "andrew";
	char s4[] = " 0123";

	reverse(s1, 4);
	printf("%s\n", s1);

	reverse(s2, 6);
	printf("%s\n", s2);

	reverse(s3, 6);
	printf("%s\n", s3);

	reverse(s4, 5);
	printf("%s\n", s4);

	return 0;
}

void reverse(char s[], int lim) {
	reverse_i(s, lim, 0);
}

void reverse_i(char s[], int lim, int i) {
	char tmp;
	if (i < lim) {
		reverse_i(s, lim - 1, i + 1);
		tmp = s[i];
		s[i] = s[lim - 1];
		s[lim - 1] = tmp;
	}
}
