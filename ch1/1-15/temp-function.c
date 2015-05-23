/*
 * Filename:	temp-function.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/23/2015
 *
 * Exercise 1.15. Rewrite the temperature conversion program
 * of Section 1.2 to use a function for conversion.
 */

#include <stdio.h>

#define LOWER	0
#define UPPER	300
#define STEP	20

float fc(float fahr);

int main(void) {
	float fahr;

	for (fahr = LOWER; fahr <= UPPER; fahr += STEP)
		printf("%3.0f %6.1f\n", fahr, fc(fahr));

	return 0;
}

float fc(float fahr) {
	return (5.0/9.0) * (fahr-32.0);
}
