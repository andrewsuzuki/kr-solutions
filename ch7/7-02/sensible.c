/*
 * Filename:    sensible.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/09/2015
 *
 * Exercise 7-2. Write a program that will print arbitrary input in a sensible way.
 * As a minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 */

#include <stdio.h>

#define MAXWIDTH 40

int printable(char);

int main(void)
{
    int c, width;

    width = 0;

    while ((c = getchar()) != EOF) {
    	if (width > MAXWIDTH || c == '\n') {
    		putchar('\n');
    		width = 0;
    		if (c == '\n')
    			continue;
    	}

    	if (printable(c)) {
    		putchar(c);
    		width++;
    	} else {
    		width += printf("0x%x", c);
    	}
    }

    return 0;
}

int printable(char c)
{
	return c >= ' ' && c <= '~';
} 