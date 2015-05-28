/*
 * Filename:	bitcount.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 2-9. In a two's complement number system, x &= (x-1)
 * deletes the rightmost 1-bit in x. Explain why. Use this
 * observation to write a faster version of bitcount.
 */

#include <stdio.h>

int bitcount(unsigned x);

int main(void) {
	printf("%d\n", bitcount(0xF)); // 4
	printf("%d\n", bitcount(0xFFF)); // 12
	printf("%d\n", bitcount(0xFAA)); // 8
	printf("%d\n", bitcount(0)); // 0

	return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x) {
	int b = 0;
	while (x != 0) {
		b++;
		x &= (x-1);
	}
	return b;
}
