/*
 * Filename:    lupper.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/09/2015
 *
 * Exercise 7-1. Write a program that converts upper case to lower or lower case
 * to upper, depending on the name it is invoked with, as found in argv[0].
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int c;

    while (!isalnum(*argv[0]))
        argv[0]++;

    while ((c = getchar()) != EOF)
        putchar((strcmp(argv[0], "upper") == 0) ? toupper(c) : tolower(c));

    return 0;
}