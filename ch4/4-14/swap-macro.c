/*
 * Filename:	swap-macro.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	06/01/2015
 *
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two
 * arguments of type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) {t tmp; tmp = x; x = y; y = tmp;}

int main(void) {
	int x, y;

	x = 1;
	y = 2;

	printf("x is %d, y is %d\n", x, y);

	swap(int, x, y);

	printf("x is %d, y is %d\n", x, y);

	return 0;
}
