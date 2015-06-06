/*
 * Filename:	detab.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/06/2015
 *
 * Exercise 5-11. Modify the programs entab and detab (written as
 * exercises in Chapter 1) to accept a list of tab stops as arguments.
 * Use the default tab settings if there are no arguments.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TABSTOP	8
#define MAX_TABSTOPS	100
#define MAXLINE			1000

void add_tabstop(int col);
int until_tabstop(int col);
void set_default_tabstop(int tabstop);

int main(int argc, char *argv[]) {
	int i, n_spec, m_spec;
	int c, col, j;
	char line[MAXLINE];

	/* add tab stops from cl arguments */
	m_spec = 0;
	n_spec = 0;
	for (i = 1; i < argc; i++) {
		if (*argv[i] == '-')
			m_spec = atoi(argv[i] + 1);
		else if (*argv[i] == '+')
			n_spec = atoi(argv[i] + 1);
	}

	if (m_spec > 0)
		add_tabstop(m_spec);

	if (n_spec > 0)
		set_default_tabstop(n_spec);

	/* convert lines */

	col = -1;
	
	while ((c = getchar()) != EOF) {
		col++;

		if (c == '\n') {
			col = -1;
		} else if (c == '\t') {
			j = until_tabstop(col);
			col += j - 1; /* fake new line position */
			for (; j > 0; --j)
				putchar(' '); /* write space until stop */
			continue;
		}

		putchar(c);
	}

	return 0;
}

int tabstops[MAX_TABSTOPS];
int tabstopp = 0;
int default_tabstop = DEFAULT_TABSTOP;

void set_default_tabstop(int tabstop) {
	default_tabstop = tabstop;
}

void add_tabstop(int col) {
	if (tabstopp < MAX_TABSTOPS)
		tabstops[tabstopp++] = col;
	else {
		printf("too many tabstops; will revert to default"
			" after %dth char in a line\n", MAX_TABSTOPS);
	}
}

/* until_tabstop: return number of characters left before next tab stop */
int until_tabstop(int col) {
	int i, last_stop, first_default;

	for (i = 0; i < tabstopp; i++)
		if (tabstops[i] > col)
			return tabstops[i] - col;

	last_stop = (tabstopp > 0) ? tabstops[tabstopp-1] : 0;

	while (col >= last_stop)
		last_stop += default_tabstop;

	return last_stop - col;
}