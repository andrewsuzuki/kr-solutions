/*
 * Filename:    isupper.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 7-9. Functions like isupper can be implemented to
 * save space or to save time. Explore both possibilities.
 *
 * ------
 *
 * On my machine, isupper1 is about 40% faster than the other two.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int isupper1(int);
int isupper2(int);
int isupper3(int);
float get_time(void);

int main(int argc, char *argv[])
{
    char test[] = "Their lesser. Sea rule. Own and divided, "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "fruitful they're. Is open moved thing won't "
                "first given, tree behold wherein a him which "
                "brought, fruitful given appear is signs lights "
                "for moving.";

    int i, len = strlen(test);

    float start, end;

    start = get_time();

    for (i = 0; i < len; i++)
        if (isupper2(test[i]))
            putchar('1');

    printf("\n%f\n", get_time() - start);

    exit(0);
}

/* c value between linear A and Z */
int isupper1(int c)
{
    return c >= 'A' && c < 'Z';
}

/* search upper set for match */
int isupper2(int c)
{
    return strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL;
}

/* search upper set for match, ordered by approx. letter frequency */
int isupper3(int c)
{
    return strchr("EOTHASINRDLUYMWFGCBPKVJQXZ", c) != NULL;
}

float get_time(void)
{
    return (float) clock() / CLOCKS_PER_SEC;
}