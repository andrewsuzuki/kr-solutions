/*
 * Filename:	strindex.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/29/2015
 *
 * Exercise 4-1. Write the function strindex(s,t) which returns the
 * position of the rightmost occurrence of t in s, or -1 if there is none.
 */

#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[]);

int main(void) {
	char s1[] = "zzzheyzzzzzyouzz";
	char t1[] = "zzz";

	printf("%d\n", strindex(s1, t1)); // 8

	return 0;
}

/* strindex: returns the position of the rightmost
 * occurrence of t in s, or -1 if there is none. */
int strindex(char s[], char t[]) {
	int i, j, k;
	int slen, tlen;

	slen = strlen(s);
	tlen = strlen(t);

	for (i = slen - 1; i >= 0; i--) { // loop s
		for (j = tlen - 1, k = 0; j >= 0; j--, k++) { // loop t
			if (s[i - k] != t[j])
				break;
		}
		if (j == -1)
			return i - (k - 1);
	}
	return -1;
}
