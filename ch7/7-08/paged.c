/*
 * Filename:    paged.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 7-8. Write a program to print a set of files, starting each new
 * one on a new page, with a title and a running page count for each file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXFILES        5
#define MAXLINE         1000
#define LINES_PER_PAGE  20

/* terminal colors */
#define KEND "\x1B[0m"
#define KRED "\x1B[31m"
#define KYLW "\x1B[33m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define BOLD "\x1B[1m"
#define UNDR "\x1B[4m"

struct file {
    FILE *fp;
    char *name;
};

char *prog;

int except = false;
int number = false;

struct file *files[MAXFILES];
int filesp = 0;

void readargs(int, char *[]);
struct file *falloc(void);
void pe(char *);
void addfile(char *, FILE *);
void resetfiles(void);

int main(int argc, char *argv[])
{
    prog = argv[0]; /* program name for errors */

    char line[MAXLINE];
    long lineno, lines_per_page;
    int i, pageno;

    lines_per_page = LINES_PER_PAGE;

    /* ARGUMENT READING AND CHECKING */

    readargs(argc - 1, ++argv);

    /* if no files were specified, print usage/error */
    if (filesp == 0) {
        pe("must supply at least one valid file");
        printf("Usage: %s file-1 ... [file-n]\n", prog);
        exit(1);
    }

    /* notify user what's happening */
    printf("Printing " BOLD "%d" KEND " file", filesp);
    printf("%s onto page(s) " BOLD "%ld " KEND, filesp > 1 ? "s" : "", lines_per_page);
    printf("lines long...\n\n");

    /* PRINT FILES */

    for (i = 0; i < filesp; i++) {
        pageno = 0;
        printf("\n" KCYN UNDR BOLD "%s" KEND "\n\n", files[i]->name);
        for (lineno = 1; fgets(line, MAXLINE, files[i]->fp) != NULL; lineno++) {
            if ((lineno - 1) % lines_per_page == 0) {
                pageno++;
                printf(KYLW "\n\tPage %d\n\n" KEND, pageno);
            }
            printf("%s", line);
        }
        printf("\n\n");
    }

    resetfiles();
    exit(0);
}

/* readargs: read filenames */
void readargs(int argc, char *argv[])
{
    for (; argc > 0; argc--) {
        addfile(*argv, fopen(*argv, "r"));
        argv++; // skip to next argument
    }
}

/* falloc: allocate memory for a file */
struct file *falloc(void) {
    return (struct file *) malloc(sizeof(struct file));
}

/* addfile: create file (with name and FILE pointer), add to files array */
void addfile(char *name, FILE *file) {
    struct file *tfp;
    tfp = falloc();
    
    tfp->name = name;

    if (file == NULL) {
        pe("couldn't open file");
        free(tfp);
        return;
    }
    tfp->fp = file;

    if (filesp < MAXFILES) {
        files[filesp++] = tfp;
    } else {
        pe("added too many files");
        free(tfp);
    }
}

/* resetfiles: free file memory and remove from array */
void resetfiles(void) {
    while (--filesp >= 0) {
        free(files[filesp]);
        files[filesp] = 0;
    }

    filesp = 0;
}

/* pe: print error to stderr with filename */
void pe(char *s)
{
    fprintf(stderr, BOLD "%s " KRED "error" KEND ": %s\n", prog, s);
}