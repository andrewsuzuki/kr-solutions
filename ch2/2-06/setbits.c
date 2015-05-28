/*
 * Filename:	setbits.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/27/2015
 *
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with
 * the n bits that begin at position p set to the rightmost n bits of y,
 * leaving the other bits unchanged.
 */

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void) {
	printf("0x%x\n", setbits(0xB5, 5, 3, 0x2B)); // 0x9d
	printf("%u\n", setbits(170, 4, 3, 7)); // 190
	printf("%u\n", setbits(4910, 6, 2, 3)); // 4974

	return 0;
}

/* setbits: returns x with the n bits that begin at position p set
 * to the rightmost n bits of y, leaving the other bits unchanged. */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned a, b, m;
	/* set bits left of y right field to zero */
	a = y & ~(~0 << n);
	/* shift right field left to position */
	a = a << (p + 1 - n);
	/* create mask with zeros at position
	 * (with ones to left and right) */
	m = (~0 << (p + 1)) | ~(~0 << (p + 1 - n));
	/* apply mask to x */
	b = x & m;
	/* set isolated y bit field into cleared-position x */
	return a | b;
}
