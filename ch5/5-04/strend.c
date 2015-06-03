/*
 * Filename:	strend.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/02/2015
 *
 * Exercse 5-4. Write the function strend(s,t), which returns 1 if the
 * string t occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>

int strend(char *s, char *t);

int main(void) {
	printf("%s\n", strend("onetwo", "two") ? "true" : "false"); // true

	printf("%s\n", strend("one2", "two") ? "true" : "false"); // false

	return 0;
}

/* strend: determines if t occurs at the end of s */
int strend(char *s, char *t) {
	char *t_o = t; /* original t pointer */
	for (; *s; s++)
		t = (*s == *t) ? t + 1 : t_o;
	return *t++ == '\0';
}
