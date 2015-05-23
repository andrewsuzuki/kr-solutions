/*
 * Filename:	word-count.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/22/2015
 *
 * Exercise 1-11. How would you test the word count program? What
 * kinds of input are most likely to uncover bugs if there are any?
 */

#include <stdio.h>

int main(void) {
	printf("If there's a sequence of characters "
		"followed by EOF, the sequence won't "
		"be counted as a word.\n");

	return 0;
}
