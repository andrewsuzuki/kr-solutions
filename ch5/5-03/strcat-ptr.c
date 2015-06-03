/*
 * Filename:	strcat-ptr.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/02/2015
 *
 * Exercise 5-3. Write a pointer version of the function strcat that we
 * showed in Chapter 2. strcat(s,t) copies the string t to the end of s.
 */

#include <stdio.h>

void _strcat(char *s, char *t);

int main(void) {
	char s[10] = "one";
	char t[10] = "two";

	_strcat(s, t);

	printf("%s\n", s);

	return 0;
}

/* _strcat: concatenate t to end of s; s must be big enough */
void _strcat(char *s, char *t) {
	while (*s) s++;
	while ((*s++ = *t++));
}
