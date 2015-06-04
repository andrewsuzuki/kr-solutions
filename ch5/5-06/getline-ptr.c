/*
 * Filename:	getline-ptr.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/03/2015
 *
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing. Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int _getline(char *s, int lim);
int strindex(char *s, char *t);

int main(void) {
	// Test _getline

	char line[MAXLINE];

	while (_getline(line, MAXLINE) != EOF)
		printf("%s", line);

	// Test _strindex
	
	//char s1[] = "zzzheyzzzzzyouzz";
	//char t1[] = "zzz";

	//printf("%d\n", strindex(s1, t1)); // 8

	return 0;
}

int _getline(char *s, int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		*s++ = c;
	*s++ = c;
	*s = '\0';
	return c;
}

int strindex(char *s, char *t) {
	int i, j, k;
	int slen, tlen;

	slen = strlen(s);
	tlen = strlen(t);

	for (i = slen - 1; i >= 0; i--) { // loop s
		for (j = tlen - 1, k = 0; j >= 0; j--, k++) { // loop t
			if (*(s + i - k) != *(t + j))
				break;
		}
		if (j == -1)
			return i - (k - 1);
	}
	return -1;
}
