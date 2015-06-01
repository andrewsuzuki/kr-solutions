/*
 * Filename:	calc-vars.c
 * Author:	Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	05/30/2015
 *
 * Exercise 4-6. Add commands for handling variables. (It's easy to provide
 * twenty-six variables with single-letter names.) Add a variable for the
 * most rececently printed variable.
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h> /* for fmod() */
#include <ctype.h>

#define MAXOP	100 /* max size of operand or operator */
#define NUMBER	'0' /* signal that a number was found */
#define CAVAR	'a' /* signal that a calc variable was found */

/* special calc function indicator codes
 * out of ascii range */
#define SET	400
#define SIN	330
#define COS	331
#define TAN	332
#define EXP	340
#define POW	350

int stackcount(void);
void push(double);
double popreal(void);
double pop(void);
double stacklastreal(void);
double stacklast(void);
void stackdup(void);
void stackswap(void);
void stackclear(void);
void stack_mark_cavar(void);
void stack_unmark_cavar(void);
int stack_is_cavar(void);
void reset_stack_mark_cavars(void);

int getop(char []);
int getch(void);
void ungetch(int);

void reset_cavars(void);
double get_cavar(int);
void set_cavar(int, double);

int main(void) {
	int type;
	double op1, op2;
	char s[MAXOP];

	reset_cavars();
	reset_stack_mark_cavars();

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case CAVAR:
				push((double) s[0]);
				stack_mark_cavar();
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
			case SET:
				op2 = popreal();
				set_cavar((int) op2, pop());
				push(get_cavar((int) op2));
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
			case 'P': /* print element at top of stack */
				printf("%f\n", stacklast());
				break;
			case 'D': /* duplicate top element */
				stackdup();
				break;
			case 'S': /* swap top two elements */
				stackswap();
				break;
			case 'C': /* clear stack */
				stackclear();
				printf("stack cleared\n");
				break;
			case '\n':
				if (stackcount() > 0) {
					printf("\t%.8g\n", stacklast());
				}
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}

	return 0;
}

/*
 * STACK
 */

#define MAXVAL 100

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* the stack */
int stack_cavars[MAXVAL]; /* marks of cavars */

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

/* pop: pop and return top value from stack;
 * if calculator variable, return variable character (a-z) */
double popreal(void) {
	if (stackcount() > 0) {
		stack_unmark_cavar();
		return val[--sp];
	} else {
		printf("error: stack empty @ pop\n");
		return 0.0;
	}
}

/* pop: pop and return top value from stack;
 * if calculator variable, return value of variable */
double pop(void) {
	if (stackcount() > 0)
		if (stack_is_cavar()) {
			stack_unmark_cavar();
			return get_cavar((int) val[--sp]);
		} else
			return val[--sp];
	else {
		printf("error: stack empty @ pop\n");
		return 0.0;
	}
}

/* stacklastreal: return top value of stack w/o popping */
double stacklastreal(void) {
	if (stackcount() > 0) {
		stack_unmark_cavar();
		return val[sp - 1];
	} else {
		printf("error: stack empty @ stacklast\n");
		return 0.0;
	}
}

/* stacklast: return top value of stack w/o popping */
double stacklast(void) {
	if (stackcount() > 0) {
		if (stack_is_cavar()) {
			stack_unmark_cavar();
			return get_cavar((int) val[sp - 1]);
		} else {
			return val[sp - 1];
		}
	} else {
		printf("error: stack empty @ stacklast\n");
		return 0.0;
	}
}

/* stackdup: duplicate top value of stack */
void stackdup(void) {
	int top_was_cavar;
	if (stackcount() > 0)
		top_was_cavar = stack_is_cavar();
		push(stacklastreal());
		if (top_was_cavar)
			stack_mark_cavar();
	else
		printf("error: stack empty @ stackdup\n");
}

/* stackswap: swap top two elements of stack */
void stackswap(void) {
	double top, bot;
	int top_was_cavar, bottom_was_cavar;

	if (stackcount() > 1) {
		top_was_cavar = stack_is_cavar();
		stack_unmark_cavar();
		top = popreal();
		bottom_was_cavar = stack_is_cavar();
		stack_unmark_cavar();
		bot = popreal();

		push(top);
		if (top_was_cavar)
			stack_mark_cavar();
		push(bot);
		if (bottom_was_cavar)
			stack_mark_cavar();
	} else
		printf("error: stack needs at least 2 elements\n");
}

/* stackclear: clear the stack */
void stackclear(void) {
	while (stackcount() > 0)
		val[--sp] = 0.0;
	reset_stack_mark_cavars();
}


/* stack_mark_cavar: mark the last-placed stack element
 * as a calculator variable (character a-z) */
void stack_mark_cavar(void) {
	stack_cavars[sp - 1] = 1;
}

/* stack_unmark_cavar: unmark the last-placed stack element
 * as a calculator variable (character a-z) */
void stack_unmark_cavar(void) {
	stack_cavars[sp - 1] = 0;
}

/* stack_is_cavar: checks if top element on stack
 * is a calculator variable (character a-z) */
int stack_is_cavar(void) {
	return stack_cavars[sp - 1] == 1;
}

/* reset_stack_mark_cavars: resets list of cavar stack marks */
void reset_stack_mark_cavars(void) {
	int i;
	for (i = 0; i < MAXVAL; i++)
		stack_cavars[i] = 0;
}

/*
 * INPUT
 */

/* getop: get next operator or numberic operand */
int getop(char s[]) {
	int i, c, th[3];

	/* skip blanks/tabs */
	while ((s[0] = c = getch()) == ' ' || c == '\t');

	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-') {
		/*
		 * Handle three-letter functions
		 * (set, sin, cos, tan, exp, pow)
		 */
		th[0] = c;

		if (th[0] == '\n') {
			return c;
		} else if (isalpha(th[0])) {
			th[1] = getch();

			if (!isalpha(th[1])) {
				ungetch(th[1]);
			} else {
				th[2] = getch();

				if (!isalpha(th[2])) {
					ungetch(th[1]);
					ungetch('\n');
				} else {
					if (th[0] == 's' && th[1] == 'e' && th[2] == 't')
						return SET;
					else if (th[0] == 's' && th[1] == 'i' && th[2] == 'n')
						return SIN;
					else if (th[0] == 'c' && th[1] == 'o' && th[2] == 's')
						return COS;
					else if (th[0] == 't' && th[1] == 'a' && th[2] == 'n')
						return TAN;
					else if (th[0] == 'e' && th[1] == 'x' && th[2] == 'p')
						return EXP;
					else if (th[0] == 'p' && th[1] == 'o' && th[2] == 'w')
						return POW;

					ungetch(th[1]);
					ungetch(th[2]);
				}
			}
		}

		/*
		 * Handle single-letter calculator variables
		 */
		if (c >= 'a' && c <= 'z') {
			return CAVAR;
		}

		return c; /* not a number, nor 3-letter cmd */
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

/*
 * CALCULATOR VARIABLES
 */

#define N_CAVARS 26

double cavars[N_CAVARS];

void reset_cavars(void) {
	int i;
	for (i = 0; i < N_CAVARS; i++)
		cavars[i] = 0.0;
}

double get_cavar(int v) {
	return cavars[v - 'a'];
}

void set_cavar(int v, double val) {
	cavars[v - 'a'] = val;
}
