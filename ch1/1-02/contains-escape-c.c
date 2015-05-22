/*
 * Filename:	contains-escape-c.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/21/2015
 *
 * Exercise 1-2. Experiment to find out what happens when prints's
 * argument string contains \c, where c is some character not listed above.
 */

#include <stdio.h>

int main(void) {
	printf("hello,\cworld\n");
	return 0;
}
