/*
 * Filename: undef.c
 * Author:	 Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:	 06/09/2015
 *
 * Exercise 6-5. Write a function undef that will remove a name and
 * definition from the table maintained by lookup and install.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *install(char *name, char *defn);
int undef(char *name);
void printtable(void);

int main(void)
{
	install("test", "this is a test1");
	install("test2", "this is a test2");
	install("test3", "this is a test3");
	install("test4", "this is a test4");
	undef("test2");
	printtable();
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

int undef(char *name)
{
	unsigned hashval;
	struct nlist *np, *last = NULL;

	for (hashval = hash(name), np = hashtab[hashval]; np != NULL; last = np, np = np->next) {
		if (strcmp(name, np->name) == 0) {
			if (last && np->next) /* was not first and has next */
				last->next = np->next;
			else if (np->next) /* was first and has next */
				hashtab[hashval] = np->next;
			else /* was first and does not have next */
				hashtab[hashval] = NULL;

			free(np->name);
			free(np->defn);
			free(np);
			
			return 1;
		}
	}
	return 0;
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