/*
 * Filename:	itob.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/29/2015
 *
 * Exercise 3-5. Write the function itob(n,s,b) that converts the integer
 * n into a base b character representation in the string s. In
 * particular, itob(n,s,16) formats s as a hexadecimal integer in s.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void itob(int n, char string[], int base);
void reverse(char s[]);

int main(void) {
	char s[1000];

	itob(0, s, 15);
	printf("%s\n", s); // 0

	itob(16, s, 16);
	printf("%s\n", s); // 10

	itob(100, s, 10);
	printf("%s\n", s); // 100

	itob(3963, s, 17);
	printf("%s\n", s); // DC2
	
	itob(295772, s, 21);
	printf("%s\n", s); // 1AJE8

	itob(-295772, s, 21);
	printf("%s\n", s); // -1AJE8 

	return 0;
}

/* itob: convert n into a base b character representation
 * in the string s (base under 37 for best results) */
void itob(int n, char s[], int b) {
	int i, sign, dig;

	sign = n;
	i = 0;
	do {
		dig = abs(n % b);
		dig += (dig < 10) ? '0' : 'A' - 10;
		s[i++] = dig;
	} while ((n /= b) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
