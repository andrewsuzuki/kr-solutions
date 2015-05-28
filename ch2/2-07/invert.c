/*
 * Filename:	invert.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the
 * n bits that begin at position p inverted (i.e., 1 changed into 0 and
 * vice versa), leaving the others unchanged.
 */

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void) {
	/* 10110101 -> 10001101 */
	printf("0x%x\n", invert(0xB5, 5, 3));
	/* 10101010 -> 10110110 */
	printf("%u\n", invert(170, 4, 3));
	/* 1001100101110 -> 1001101001110 */
	printf("%u\n", invert(4910, 6, 2));

	return 0;
}

/* invert: returns x with the n bits that begin at position p inverted */
unsigned invert(unsigned x, int p, int n) {
	unsigned m;
	/* create mask with ones covering field
	 * (with zeros to left and right) */
	m = ~((~0 << (p + 1)) | ~(~0 << (p + 1 - n)));
	/* xor mask with x to invert bits in field */
	return x ^ m;
}
