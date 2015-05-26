/*
 * Filename:	var-range.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/24/2015
 *
 * Exercise 2-1. Write a program to determine the ranges of char, short,
 * int, and long variables, both signed and unsigned, by printing
 * appropriate values from standard headers and by direct computation.
 * Harder if you compute them: determine the ranges of the various
 * floating-point types.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
	printf("Range of unsigned char: %d to %d\n", 0, UCHAR_MAX);
	printf("Range of signed char: %d to %d\n", SCHAR_MIN, SCHAR_MAX);

	printf("Range of unsigned short: %d to %d\n", 0, USHRT_MAX);
	printf("Range of signed short: %d to %d\n", SHRT_MIN, SHRT_MAX);

	printf("Range of unsigned int: %d to %d\n", 0, UINT_MAX);
	printf("Range of signed int: %d to %d\n", INT_MIN, INT_MAX);

	printf("Range of unsigned long: %lu to %lu\n", 0L, ULONG_MAX);
	printf("Range of signed long: %ld to %ld\n", LONG_MIN, LONG_MAX);

	printf("Range of float: %f to %f\n", FLT_MIN, FLT_MAX);

	printf("Range of double: %f to %f\n", DBL_MIN, DBL_MAX);

	return 0;
}
