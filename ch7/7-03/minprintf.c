/*
 * Filename:    minprintf.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/09/2015
 *
 * Exercise 7-3. Revise minprintf to handle more of the facilities of printf.
 */

#include <stdio.h>
#include <stdarg.h>

typedef char *String;

void minprintf(String, ...);

int main(void)
{
    int test = 9001;

    minprintf("i <%d you\n", 3);
    minprintf("nvm, %s%i%s", "</", 3, "\n");
    minprintf("%E\n", 1119.32334);
    minprintf("%G\n", 1119.32334);
    minprintf("100%%\n");
    minprintf("%x\n", 300);
    minprintf("%p\n", &test);

    return 0;
}

void minprintf(String fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    String p, sval;
    int ival;
    unsigned uval;
    double dval;
    void *pval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch(*++p) {
        case 'i':
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'c':
            ival = va_arg(ap, int);
            printf("%c", ival);
            break;
        case 'o':
            uval = va_arg(ap, unsigned int);
            printf("%o", uval);
            break;
        case 'X':
        case 'x':
            uval = va_arg(ap, unsigned int);
            printf("%x", uval);
            break;
        case 'u':
            uval = va_arg(ap, unsigned int);
            printf("%u", uval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'E':
        case 'e':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'G':
        case 'g':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        case 's':
            for (sval = va_arg(ap, String); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* clean up when done */
} 