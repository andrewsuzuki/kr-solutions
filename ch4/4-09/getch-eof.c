/*
 * Filename:	getch-eof.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/31/2015
 *
 * Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF
 * correctly. Decide what their properties ought to be if an EOF is
 * pushed back, then implement your design.
 *
 * *** The only change was changing the type of buf[] from char to int.
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h> /* for fmod() */
#include <ctype.h>
#include <string.h> /* for strcmp() */

#define MAXOP	100 /* max size of operand or operator */
#define NUMBER	'0' /* signal that a number was found */
#define UNKNOWN 'u' /* signal for unknown command */

#define SIN	330
#define COS	331
#define TAN	332
#define EXP	340
#define POW	350
#define GET	400
#define SET	401

int getop(char []);
int count(void);
void push(double);
double pop(void);
double last(void);
double getvar(char var);
void setvar(char var, double value);

int main(void) {
	int type;
	double op1, op2;
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
			case SIN:
				push(sin(pop()));
				break;
			case COS:
				push(cos(pop()));
				break;
			case TAN:
				push(tan(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				op1 = pop();
				if (op1 == 0 && op2 <= 0)
					printf("error: pow domain error\n");
				else
					push(pow(op1, op2));
				break;
			case GET:
				push(getvar(s[0]));
				break;
			case SET:
				setvar(s[0], last());
				break;
			case '\n':
				if (count() > 0)
					printf("\t%.8g\n", last());
				break;
			case UNKNOWN:
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}

	return 0;
}

#define MAXVAL 100

int sp = 0; /* next free stack position */
double stack[MAXVAL]; /* the stack */

/* count: count elements in stack */
int count(void) {
	return sp;
}

/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
	if (count() > 0)
		return stack[--sp];
	else {
		printf("error: stack empty @ pop\n");
		return 0.0;
	}
}

/* last: return top value of stack w/o popping */
double last(void) {
	if (count() > 0)
		return stack[sp-1];
	else {
		printf("error: stack empty @ stacklast\n");
		return 0.0;
	}
}

#define N_VARS 26

double vars[N_VARS];

double getvar(char v) {
	return vars[v - 'a'];
}

void setvar(char v, double val) {
	vars[v - 'A'] = val;
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

	if (c == '\n' || c == EOF)
		return c;

	i = 0;

	if (isalpha(c)) {
		while (isalpha(s[++i] = c = getch()));
		/* undo side effects */
		ungetch(c);
		s[i] = '\0';
		/* match to command or variable */
		if (i > 1) {
			/* probably command */
			if (strcmp(s, "sin") == 0)
				return SIN;
			else if (strcmp(s, "cos") == 0)
				return COS;
			else if (strcmp(s, "tan") == 0)
				return TAN;
			else if (strcmp(s, "exp") == 0)
				return EXP;
			else if (strcmp(s, "pow") == 0)
				return POW;
			else
				return UNKNOWN;
		} else {
			/* probably var */
			if (islower(s[0]))
				return GET;
			else
				return SET;
		}
	} else if (isdigit(c)) {
		/* collect integer part */
		while (isdigit(s[++i] = c = getch()));
		if (c == '.')
			while (isdigit(s[++i] = c = getch()));
		/* undo side effects */
		ungetch(c);
		s[i] = '\0';
		/* return */
		return NUMBER;
	}

	return c;
}

#define BUFSIZE 100

int buf[BUFSIZE];
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
