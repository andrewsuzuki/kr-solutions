/*
 * Filename:	rightrot.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 2-8. Write a function rightrot(x,n) that returns the
 * value of the integer x rotated to the right by n positions.
 */

#include <stdio.h>

unsigned rightrot(unsigned x, int n);
unsigned wordsize(void);

int main(void) {
	printf("Word size: %d\n", wordsize());
	/* 10110101 -> 10101...0...101 */
	printf("0x%x\n", rightrot(0xB5, 5));
	/* should be same as above */
	printf("0x%x\n", rightrot(0xB5, 5 + wordsize()));
	/* 10101010 -> 1010...0...1010 */
	printf("%u\n", rightrot(170, 4));
	/* 1001100101110 -> 101110...0...1001100 */
	printf("%u\n", rightrot(4910, 6));

	return 0;
}

/* rightrot: returns integer x rotated to the right by n positions */
unsigned rightrot(unsigned x, int n) {
	unsigned ws, a, b;
	/* determine word size i */
	ws = wordsize();
	/* if shift amount n is greater than the
	 * word size, let's fake n and only
	 * rotate it the number of times 
	 * to get the equivalent result */
	while (n > ws) n -= ws;
	/* create right half of result */
	a = x >> n;
	/* create left half of result */
	b = x << (ws - n);
	/* merge halves */
	return a | b;
}

/* wordsize: returns size of machine's natural word */
unsigned wordsize(void) {
	unsigned i, full;
	full = ~0u;
	for (i = 1; (full = full >> 1) > 0; i++);
	return i;
}
