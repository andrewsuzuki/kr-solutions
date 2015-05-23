/*
 * Filename:	eof-value.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
 */

#include <stdio.h>

int main(void) {
	printf("Char: ");
	printf("(getchar() != EOF) == %d\n", getchar() != EOF);

	return 0;
}
