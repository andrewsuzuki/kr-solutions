/*
 * Filename:	nccc.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/02/2015
 *
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp,
 * which operate on at most the first n characters of their argument strings. For
 * example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions
 * are in Appendix B.
 */

#include <stdio.h>

void _strncpy(char *s, char *t, int n);
void _strncat(char *s, char *t, int n);
int _strncmp(char *s, char *t, int n);

int main(void) {
	char s1[100];
	char t1[] = "test";
	_strncpy(s1, t1, 3);
	printf("%s\n", s1); // tes
	printf("%s\n", _strncmp(s1, "test", 4) == 0 ? "true" : "false"); // false
	printf("%s\n", _strncmp(s1, "test", 3) == 0 ? "true" : "false"); // true
	printf("%s\n", _strncmp("test", "test", 5) == 0 ? "true" : "false"); // true
	_strncat(s1, "selation nope nope nope", 8);
	printf("%s\n", _strncmp(s1, "tesselation", 11) == 0 ? "true" : "false"); // true

	return 0;
}

void _strncpy(char *s, char *t, int n) {
	int i;
	for (i = 0; i < n && (*s++ = *t++); i++);
	for (; i < n || *s; i++)
		*s++ = '\0';
}

void _strncat(char *s, char *t, int n) {
	int i;
	while (*s) s++;
	for (i = 0; i < n && (*s++ = *t++); i++);
	if (*s) *s++ = '\0';
}

int _strncmp(char *s, char *t, int n) {
	int i;
	for (i = 0; i < n && (*s == *t); i++, s++, t++)
		if (*s == '\0' || i == n - 1)
			return 0;
	return (*s == *t) ? 0 : *s - *t;
}
