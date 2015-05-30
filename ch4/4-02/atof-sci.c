/*
 * Filename:	atof-sci.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/29/2015
 *
 * Exercise 4-2. Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an
 * optionally signed exponent.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

double atof(char s[]);

int main(void) {
	double atof(char []); /* lesson of this section */

	printf("%f\n", atof("123.123")); // 123.123000
	printf("%f\n", atof("123.45E6")); // 123450000.000000
	printf("%f\n", atof("123.45e-6")); // 0.000123

	return 0;
}

/* atof: convert string s to double */
double atof(char s[]) {
	double val, power, expmult;
	int i, sign, exp, expsign;

	for (i = 0; isspace(s[i]); i++); /* skip white space */

	sign = (s[i] == '-') ? -1 : 1; /* determine sign */

	if (s[i] == '+' || s[i] == '-') /* skip over opt sign */
		i++;

	for (val = 0.0; isdigit(s[i]); i++) /* get integer part */
		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) { /* get decimal part */
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}

	if (s[i] == 'e' || s[i] == 'E')
		i++;

	expsign = (s[i] == '-') ? -1 : 1; /* determine exponent sign */

	if (s[i] == '+' || s[i] == '-') /* skip over opt sign */
		i++;

	for (exp = 0; isdigit(s[i]); i++) /* get exponent int */
		exp = 10 * exp + (s[i] - '0');

	/* determine final exp multiplier (10^exp) */
	for (expmult = 1.0; exp > 0; exp--)
		expmult *= 10;
	if (expsign == -1 && expmult != 0)
		expmult = 1 / expmult;

	return sign * val * expmult / power;
}
