/*
 * Filename:	cel-to-fahr.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/21/2015
 *
 * Exercise 1-4. Write a program to print the corresponding
 * Celsius to Fahrenheit table.
 */

#include <stdio.h>

int main(void) {
	float fahr, celsius;
	float lower, upper, step;

	lower = -100;
	upper = 200;
	step = 20;

	celsius = lower;
	printf("Celsius Fahrenheit\n");
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%7.0f %10.1f\n", celsius, fahr);
		celsius = celsius + step;
	}

	return 0;
}
