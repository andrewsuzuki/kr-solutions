/*
 * Filename:	expr.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/05/2015
 *
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is
 * a serparate argument. For example, expr 2 3 4 + * evaluates 2*(3+4)
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

#define NUM 1

#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5

int getop(char *arg, double *num);

int main(int argc, char *argv[]) {
	int n = 0;
	double num;
	double op2;
	while (++n < argc) {
		switch (getop(argv[n], &num)) {
			case NUM:
				push(num);
				break;
			case ADD:
				push(pop() + pop());
				break;
			case SUB:
				op2 = pop();
				push(pop() - op2);
				break;
			case MUL:
				push(pop() * pop());
				break;
			case DIV:
				op2 = pop();
				push(pop() / op2);
				break;
			default:
				printf("command \"%s\" not recognized\n", argv[n]);
				break;
		}
	}

	printf("result: %f\n", pop());
	return 0;
}

int getop(char *arg, double *num) {
	if (*arg == '+')
		return ADD;
	else if (*arg == '-')
		return SUB;
	else if (*arg == 'x')
		return MUL;
	else if (*arg == '/')
		return DIV;
	else if (isdigit(*arg)) {
		*num = 0.0;
		double tmp;
		for (; isdigit(*arg); arg++) {
			tmp = *num * 10.0 + (*arg - '0');
			*num = tmp;
		}
		return NUM;
	} else
		return *arg;
}