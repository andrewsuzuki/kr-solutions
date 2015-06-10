/*
 * Filename:    minscanf.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 7-4. Write a private version of scanf analogous
 * to minprintf from the previous version.
 */

#include <stdio.h>
#include <stdarg.h>

typedef char *String;

int minscanf(String, ...);

int main(void)
{
    int sum, v;

    sum = 0;
    while (minscanf("%d", &v) == 1)
        printf("\t%d\n", sum += v);

    return 0;
}

int minscanf(String fmt, ...)
{
    int sfr = 1;
    va_list ap; /* points to each unnamed arg in turn */
    String p;
    int *ival;
    unsigned *uval;
    char *cval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch(*++p) {
        case 'i':
        case 'd':
            ival = va_arg(ap, int *);
            sfr = scanf("%d", ival);
            break;
        case 'o':
            ival = va_arg(ap, int *);
            sfr = scanf("%o", ival);
            break;
        case 'u':
            uval = va_arg(ap, unsigned int *);
            sfr = scanf("%u", uval);
            break;
        case 'x':
            ival = va_arg(ap, int *);
            sfr = scanf("%x", ival);
            break;
        case 'c':
            cval = va_arg(ap, char *);
            sfr = scanf("%c", cval);
            break;
        default:
            // nothing
            break;
        }

        if (sfr != 1)
            return sfr;
    }
    va_end(ap); /* clean up when done */
    return 1;
} 