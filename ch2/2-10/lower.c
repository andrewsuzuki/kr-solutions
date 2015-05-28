/*
 * Filename:	lower.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 2-10. Rewrite the function lower, which converts upper case
 * letters to lower case, with a conditional expression instead of if-else.
 */

#include <stdio.h>

void lower(char string[]);

int main(void) {
	char s1[] = "HeLlO";
	char s2[] = "Hi, My Name is andrew";

	lower(s1);
	lower(s2);

	printf("%s\n", s1);
	printf("%s\n", s2);

	return 0;
}

void lower(char s[]) {
	int i;
	for (i = 0; s[i] != '\0'; i++)
		s[i] += (s[i] >= 'A' && s[i] <= 'Z') ? ('a' - 'A') : 0;
}
