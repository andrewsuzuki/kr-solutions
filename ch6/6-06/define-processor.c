/*
 * Filename:    define-processor.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/09/2015
 *
 * Exercise 6-6. Write a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of
 * this section. You may also find getch and ungetch helpful.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE    101
#define MAXWORD     100
#define MAXLINE     1000

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *install(char *name, char *defn);
void printtable(void);

int _getline(char *s, int lim);

int main(void)
{
    int c;
    char line[MAXLINE];
    struct nlist *rep;

    while ((c = _getline(line, MAXLINE))) {
        printf("%s", line);
        if (c == EOF) break;
    }

    return 0;
}

void printtable(void)
{
    unsigned hash;
    struct nlist *np;

    for (hash = 0; hash < HASHSIZE; hash++) {
        printf("%d: ", hash);
        for (np = hashtab[hash]; np != NULL; np = np->next)
            printf("(%s: %s) %s", np->name, np->defn, (np->next == NULL) ? "" : "-- ");
        printf("\n");
    }
}

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

char *_strdup(char *);

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = _strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if ((np->defn = _strdup(defn)) == NULL)
        return NULL;

    return np;
}

/* strdup: make a duplicate of s */
char *_strdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int in_comment = false;
int in_quote = false;
int in_hashcom = false;

int getch(void);

int _getline(char *s, int lim) {
    int c, lc, i, j, k, r, spaces, record, record_word;
    char word1[MAXWORD], word2[MAXWORD];
    struct nlist *match;

    c = lc = i = j = k = r = spaces = 0;

    record = record_word = false;

    for (i = 0; i < lim - 1 && (c = getch()) != EOF && c != '\n'; i++) {
        *(s + i) = c;
        *(s + i + 1) = '\0';

        if (!in_comment && !in_quote) {
            /* parse define lines */

            if (i == 6 && strcmp(s, "#define") == 0) {
                record = true;
                j = 0;
            }

            if (record) {
                if (isspace(c) && !isspace(lc)) {
                    /* beginning of space section */
                    spaces++;
                }

                if (spaces == 1 && (isalnum(c) || c == '_'))
                    word1[j++] = c;
                else if (spaces == 2 && (isalnum(c) || c == '_'))
                    word2[k++] = c;
            }

            /* check words definition replacement */

            if (!record) {
                if (record_word && (!isalnum(c) && c != '_')) {
                    word1[j] = '\0';
                    if ((match = lookup(word1))) {
                        /* j is length of original */
                        /* r is length of replacement */
                        /* k is the k-th replacement char */
                        r = strlen(match->defn);
                        i -= j;
                        for (k = 0; k < r && i < lim - 1; k++, i++)
                            *(s + i) = match->defn[k];
                        *(s + i) = c;
                        *(s + i + 1) = '\0';
                    }
                    record_word = false;
                    j = 0;
                } else if (!record_word && (isalnum(c) || c == '_'))
                    record_word = true;

                if (record_word)
                    word1[j++] = c;
            }
        }

        lc = c;
    }
    
    word1[j] = word2[k] = '\0';

    /* if it was a define, install definition */
    if (strlen(word1) && strlen(word2))
        install(word1, word2);

    *(s + i) = '\n';
    *(s + i + 1) = '\0';

    return c;
}

int getch(void) {
    int c;
    static int lc = -1;

    c = getchar();

    if (c == EOF) return EOF; 

    if (lc == '/' && c == '*') {
        in_comment = true;
    } else if (in_comment && lc == '*' && c == '/') {
        in_comment = false;
    } else if (!in_comment && c == '"' && lc != '\\' && lc != '\'') {
        in_quote = !in_quote;
    } else if (!in_comment && !in_quote && c == '#') {
        in_hashcom = true;
    } else if (in_hashcom && c == '\n')
        in_hashcom = false;

    lc = c;
    return c;
}