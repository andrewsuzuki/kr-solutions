/*
 * Filename:	squeeze.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/26/2015
 *
 * Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */

#include <stdio.h>
#include <stdbool.h>

#define CHAR_SET_SIZE 128 

void squeeze(char string1[], char string2[]);

int main(void) {
	char s1[] = "here comes johnny";
	char s2[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	char s3[] = "bbbbaaaacddddd";

	squeeze(s1, "nile");
	squeeze(s2, "acegikmoqsuwy02468");
	squeeze(s3, "ad");

	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("%s\n", s3);

	return 0;
}

void squeeze(char s1[], char s2[]) {
	int i, offset;
	bool found[CHAR_SET_SIZE];

	/* reset found array */
	for (i = 0; i < CHAR_SET_SIZE; i++)
		found[i] = false;

	/* mark all characters found in s2 */
	for (i = 0; s2[i] != '\0'; i++)
		found[s2[i]] = true;

	offset = 0;

	for (i = 0; s1[i] != '\0'; i++) {
		if (found[s1[i]]) {
			/* if this char exists in s2, delete and
			 * increment offset (for later chars) */
			s1[i] = 0;
			offset++;
		} else if (offset) {
			/* otherwise, if a previous char was deleted,
			 * shift this char to the left and delete current */
			s1[i - offset] = s1[i];
			s1[i] = 0;
		}
	}

	s1[i - offset] = '\0'; /* mark end of string */
}
