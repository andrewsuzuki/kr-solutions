/*
 * Filename:	escape.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/28/2015
 *
 * Exercise 3-2. Write a function escape(s,t) that converts characters
 * like newline and tab into visible escape sequences like \n and \t
 * as it copies the string t to s. Use a switch. Write a function
 * for the other direction as well, converting escape sequences
 * into the real characters.
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_STR_SIZE 1000

void escape(char to[], char from[]);
void unescape(char to[], char from[]);

int main(void) {
	char s1[] = "This\nis\na\ttest";
	char t1[MAX_STR_SIZE];
	char u1[MAX_STR_SIZE];

	printf("%s\n", s1);

	escape(t1, s1);

	printf("%s\n", t1);

	unescape(u1, t1);

	printf("%s\n", u1);

	return 0;
}

/* escape: converts newline/tab to \n and \t from t to s */
void escape(char s[], char t[]) {
	int i, j;
	j = 0;
	for (i = 0; t[i] != '\0'; i++) {
		switch(t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	}
	s[j] = '\0';
}

/* unescape: converts visual \n and \t to actual newline and tab from t to s */
void unescape(char s[], char t[]) {
	int i, j, last_slash;
	j = 0;
	last_slash = false;
	for (i = 0; t[i] != '\0'; i++) {
		if (last_slash) {
			last_slash = false;
			switch (t[i]) {
				case 'n':
					s[j++] = '\n';
					break;
				case 't':
					s[j++] = '\t';
					break;
				default:
					s[j++] = '\\';
					s[j++] = t[i];
					break;
			}
		} else {
			if (t[i] == '\\')
				last_slash = true;
			else
				s[j++] = t[i];
		}
	}
	s[j] = '\0';
}
