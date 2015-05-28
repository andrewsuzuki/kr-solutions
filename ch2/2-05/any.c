/*
 * Filename:	any.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/27/2015
 *
 * Exercise 2-5. Write the function any(s1,s2), which returns the first location
 * in a string s1 where any character from the string s2 occurs, or -1 if s1
 * contains no characters from s2. (The standard library function strpbrk
 * does the same job but returns a pointer to the location.)
 */

#include <stdio.h>
#include <stdbool.h>

#define CHAR_SET_SIZE 128 

int any(char string1[], char string2[]);

int main(void) {
	char s1[] = "here comes johnny";
	char s2[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	char s3[] = "bbbbaaaacddddd";

	printf("%d\n", any(s1, "nile"));
	printf("%d\n", any(s2, "acegikmoqsuwy02468"));
	printf("%d\n", any(s3, "ad"));

	return 0;
}

int any(char s1[], char s2[]) {
	int i;
	bool found[CHAR_SET_SIZE];

	/* reset found array */
	for (i = 0; i < CHAR_SET_SIZE; i++)
		found[i] = false;

	/* mark all characters found in s2 */
	for (i = 0; s2[i] != '\0'; i++)
		found[s2[i]] = true;

	for (i = 0; s1[i] != '\0'; i++)
		if (found[s1[i]])
			return i;

	return -1;
}
