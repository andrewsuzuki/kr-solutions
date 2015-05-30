/*
 * Filename:	calc-ptop.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/30/2015
 *
 * Exercise 4-4. Add commands to print the top element of the stack without
 * popping, to duplicate it, and to swap the top two elements. Add a command
 * to clear the stack.
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h> /* for fmod() */

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
int stackcount(void);
void push(double);
double pop(void);
double stacklast(void);
void stackdup(void);
void stackswap(void);
void stackclear(void);

int main(void) {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: zero modulo\n");
				break;
			case 'P':
				printf("%f\n", stacklast());
				break;
			case 'D':
				stackdup();
				break;
			case 'S':
				stackswap();
				break;
			case 'C':
				stackclear();
				printf("stack cleared\n");
				break;
			case '\n':
				if (stackcount() > 0)
					printf("\t%.8g\n", stacklast());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}

	return 0;
}

#define MAXVAL 100

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* the stack */

/* stackcount: count elements in stack */
int stackcount(void) {
	return sp;
}

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (stackcount() > 0)
		return val[--sp];
	else {
		printf("error: stack empty @ pop\n");
		return 0.0;
	}
}

/* stackdup: duplicate top value of stack */
void stackdup(void) {
	if (stackcount() > 0)
		push(stacklast());
	else
		printf("error: stack empty @ stackdup\n");
}

/* stackswap: swap top two elements of stack */
void stackswap(void) {
	double top, bot;
	if (stackcount() > 1) {
		top = pop();
		bot = pop();
		push(top);
		push(bot);
	} else
		printf("error: stack needs at least 2 elements\n");
}

/* stackclear: clear the stack */
void stackclear(void) {
	while (stackcount() > 0)
		val[--sp] = 0.0;
}

/* stacklast: return top value of stack w/o popping */
double stacklast(void) {
	if (stackcount() > 0)
		return val[sp-1];
	else {
		printf("error: stack empty @ stacklast\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numberic operand */
int getop(char s[]) {
	int i, c;

	/* skip blanks/tabs */
	while ((s[0] = c = getch()) == ' ' || c == '\t');

	s[1] = '\0';
	if (!isdigit(c) && c != '.') {
		return c; /* not a number */
	}
	i = 0;
	if (c == '-')
		s[++i] = c = getch();
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { /* get a (possibly pushed back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
