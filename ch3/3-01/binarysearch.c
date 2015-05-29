/*
 * Filename:	binarysearch.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 3-1. Our binary search makes two tests inside the loop,
 * when one would suffice (at the price of more tests outside.)
 * Write a version with only one test inside the loop and
 * measure the difference in run-time.
 */

#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void) {
	int test[7] = {1, 3, 5, 7, 9, 11, 13};

	printf("%d\n", binsearch(test[0], test, 7));
	printf("%d\n", binsearch(test[1], test, 7));
	printf("%d\n", binsearch(test[2], test, 7));
	printf("%d\n", binsearch(test[3], test, 7));
	printf("%d\n", binsearch(test[4], test, 7));
	printf("%d\n", binsearch(test[5], test, 7));
	printf("%d\n", binsearch(test[6], test, 7));
	printf("%d\n", binsearch(15, test, 7));

	return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}

	return (x == v[low]) ? low : -1;
}
