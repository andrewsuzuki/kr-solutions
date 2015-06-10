/*
 * Filename:    pattern.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/10/2015
 *
 * Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its
 * input from a set of named files or, if no files are named as arguments,
 * from the standard input. Should the file name be printed when a
 * matching file is found?
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXFILES 5
#define MAXLINE  1000

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
char *pattern;

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
    long lineno;
    int i;

    /* ARGUMENT READING AND CHECKING */
    
    if (argc == 1) {
        printf("Usage: %s -xn [file-1] ... [file-n] pattern\n", prog);
        pe("must supply a pattern");
        exit(1);
    }

    readargs(argc - 1, ++argv);

    /* notify what's happening */
    printf("Searching " BOLD "%d" KEND " file", filesp);
    printf("%s for lines with", filesp > 1 ? "s" : "");
    printf("%s ", except ? UNDR "out" KEND : "");
    printf(BOLD "%s" KEND "...\n\n", pattern);

    /* if no files were specified, use stdin */
    if (filesp == 0) {
        addfile("stdin", stdin);
        printf(KYLW "did not specify file; will use " BOLD "stdin\n" KEND);
    }

    /* SEARCH FILES */

    for (i = 0; i < filesp; i++) {
        printf(KCYN BOLD "%s" KEND ":\n", files[i]->name);
        for (lineno = 1; fgets(line, MAXLINE, files[i]->fp) != NULL; lineno++) {
            if ((strstr(line, pattern) != NULL) != except) {
                if (number)
                    printf(KWHT "%ld:" KEND, lineno);
                printf("%s", line);
            }
        }
        putchar('\n');
    }

    resetfiles();
    exit(0);
}

/* readargs: read options and filenames */
void readargs(int argc, char *argv[])
{
    int c;

    for (; argc > 0; argc--) {
        if (argc == 1) { // assume last argument is pattern
            pattern = *argv;
        } else if ((*argv)[0] == '-') { // is option
            while ((c = *++argv[0])) {
                switch (c) {
                    case 'x':
                        except = true;
                        break;
                    case 'n':
                        number = true;
                        break;
                    default:
                        pe("used illegal option");
                }
            }
        } else { // is file
            addfile(*argv, fopen(*argv, "r"));
        }

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