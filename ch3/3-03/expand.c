/*
 * Filename:	expand.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list abc...xyz in s2.
 * Allow for letters of either case and digits, and be prepared to handle cases
 * like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is
 * taken literally.
 */

#include <stdio.h>
#include <ctype.h>

#define MAX_TEST_SIZE 1000

void expand(char to[], char from[]);

int main(void) {
	char s1[] = "These are lowercase: a-z\nAnd these are uppercase: A-Z\nDigits: 0-9";
	char t1[MAX_TEST_SIZE];

	/* yields abcABCDEF01234 */
	char s2[] = "a-b-cA-F0-3-3-4";
	char t2[MAX_TEST_SIZE];

	/* yields a-Z-0 */
	char s3[] = "a-Z-0";
	char t3[MAX_TEST_SIZE];

	expand(t1, s1);
	expand(t2, s2);
	expand(t3, s3);

	printf("%s\n", t1);
	printf("%s\n", t2);
	printf("%s\n", t3);

	return 0;
}

void expand(char t[], char f[]) {
	int i, j, k, from, to, inc;
	j = 0;
	for (i = 0; f[i] != '\0'; i++) {
		if (i >= 2 && f[i - 1] == '-') {
			/* check if range is same type (both lower/upper/digit) */
			if ((islower(f[i]) && islower(f[i - 2])) ||
			(isupper(f[i]) && isupper(f[i - 2])) ||
			(isdigit(f[i]) && isdigit(f[i - 2])))
			{
				/* get range */
				from = f[i - 2];
				to = f[i];
				/* determine range direction */
				inc = (from > to) ? -1 : 1;
				/* rewrite past two chars */
				j -= 2;
				/* write range */
				for (k = from; k <= to; k += inc)
					t[j++] = k;
				continue;
			}
		}
		/* default */
		t[j++] = f[i];
	}
	t[j] = '\0';
}
