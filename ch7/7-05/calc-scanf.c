/*
 * Filename:    calc-scanf.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use
 * scanf to do the input and number conversion.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 /* max size of operand or operator */

void push(double);
double pop(void);

int main(void)
{
    int type;
    double num, op2;
    char *c;
    char d, s[MAXOP], v[MAXOP];

    while (scanf("%s%c", s, &d) == 2) {
        if (sscanf(s, "%lf", &num) == 1) {
            push(num);
        } else if (sscanf(s, "%s", v) == 1) {
            for (c = v; *c; c++) {
                switch (*c) {
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
                    default:
                        printf("error: unknown command %s\n", s);
                        break;
                }
            }

            if (d == '\n')
                printf("\t%.8g\n", pop());
        }
    }

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}