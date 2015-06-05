#include "stack.h"

double stack[STACK_SIZE];
int stackp = 0;

void push(double value) {
	if (stackp < STACK_SIZE) {
		stack[stackp++] = value;
	}
	else
		printf("error: stack full\n");
}

double pop(void) {
	if (stackp > 0) {
		return stack[--stackp];
	} else {
		printf("error: stack empty\n");
		return 0;
	}
}