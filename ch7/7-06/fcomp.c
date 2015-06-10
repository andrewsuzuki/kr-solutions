/*
 * Filename:    fcomp.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 7-6. Write a program to compare two files, printing the
 * first line where they differ.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

#define KEND "\x1B[0m"
#define KRED "\x1B[31m"
#define KCYN "\x1B[36m"
#define BOLD "\x1B[1m"

#define forever(void) while(1)

void close2(FILE *, FILE *);
void pm(int);
void pl(int);
void pe(char *);

char *prog;

int main(int argc, char *argv[])
{
    prog = argv[0]; /* program name for errors */

    FILE *fp1;
    FILE *fp2;
    char x[MAXLINE], y[MAXLINE];
    char *r1, *r2;
    int n;

    if (argc != 3)
        pe("must supply exactly two filenames");
    if ((fp1 = fopen(argv[1], "r")) == NULL)
        pe("can't open first file");
    if ((fp2 = fopen(argv[2], "r")) == NULL)
        pe("can't open second file");

    n = 0;

    forever() {
        n++;

        r1 = fgets(x, MAXLINE, fp1);
        r2 = fgets(y, MAXLINE, fp2);

        if (r1 == NULL && r1 == r2) { // both null
            close2(fp1, fp2);
            pm(n);
        } else if ((r1 == NULL || r2 == NULL) && r1 != r2) { // one null
            close2(fp1, fp2);
            pl(n);
        } else if (strcmp(x, y) != 0) {
            close2(fp1, fp2);
            pl(n);
        }
    }

    exit(0);
}

/* close2: close two files */
void close2(FILE *fp1, FILE *fp2)
{
    fclose(fp1);
    fclose(fp2);
}

/* pm: print that files match */
void pm(int line)
{
    printf(KCYN "files match completely!\n" KEND);
    exit(0);
}

/* pl: print line where files differ */
void pl(int line)
{
    printf("files differ at " KCYN "line %d\n" KEND, line);
    exit(0);
}

/* pe: print error to stderr with filename */
void pe(char *s)
{
    fprintf(stderr, BOLD "%s " KRED "error" KEND ": %s\n", prog, s);
    exit(1);
}