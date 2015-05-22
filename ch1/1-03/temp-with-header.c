/*
 * Filename:	temp-with-header.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/21/2015
 *
 * Exercise 1-3. Modify the temperature conversion program to
 * print a heading above the table.
 */

#include <stdio.h>

int main(void) {
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	printf("Fahrenheit Celsius\n");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%10.0f %7.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
