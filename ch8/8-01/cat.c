/*
 * Filename:    cat.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write,
 * open and close instead of their standard library equivalents. Perform
 * experiments to determine the relative speeds of the two versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/file.h>

/* terminal colors */
#define KEND "\x1B[0m"
#define KRED "\x1B[31m"
#define KYLW "\x1B[33m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define BOLD "\x1B[1m"
#define UNDR "\x1B[4m"

void printfile(int);
void error(char *);

int main(int argc, char *argv[])
{
    char *prog = argv[0];
    char *usage = "usage: cat file-1 ... [file-n]\n";
    int fd;

    if (argc == 1) {
        write(2, usage, strlen(usage));
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                error("can't open file");
            } else {
                printfile(fd);
            }
        }
    }
    
    exit(0);
}

/* printfile: prints file with given file descriptor to stdout */
void printfile(int fd)
{
    int n;
    char buf[BUFSIZ];

    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        if (write(1, buf, n) != n) {
            error("write error on file");
        }
    }
}

/* pe: print error to stderr */
void error(char *s)
{
    char *m = BOLD "cat " KRED "error" KEND ": ";
    write(2, m, strlen(m));
    write(2, s, strlen(s));
    write(2, "\n", 1);
    exit(1);
}