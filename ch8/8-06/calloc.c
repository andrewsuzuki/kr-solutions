/*
 * Filename:    calloc.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/12/2015
 *
 * Exercise 8-6. The standard library function callloc(n,size) returns a
 * pointer to n objects of size size, with the storage initialized to
 * zero. Write calloc, by calling malloc or by modifying it.
 */

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <time.h>
// #include <fcntl.h>
#include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <dirent.h>

typedef long Align; /* for alignment to long boundary */

union header {
    struct {
        union header *ptr; /* next block if on free list */
        unsigned size; /* the size of the next block */
    } s;
    Align x; /* force alignment of blocks */
};

typedef union header Header;

static Header base; /* empty list to get started */
static Header *freep = NULL;

/* my_free: put block ap in free list */
void my_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p) && bp < p->s.ptr; p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;
        }
    }

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}

#define NALLOC 1024 /* minimum #units to request */

/* my_morecore: ask system for more memory */
static Header *my_morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) - 1) /* no space at all */
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;

    my_free((void *)(up + 1));

    return freep;
}

/* my_malloc: general-purpose storage allocator */
void *my_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) { /* exactly */
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;

            return (void *)(p + 1);
        }

        if (p == freep) { /* wrapped around free list */
            if ((p = my_morecore(nunits)) == NULL) {
                return NULL; /* none left */
            }
        }
    }
}

void *my_calloc(unsigned nobj, unsigned nbytes)
{
    int i;
    Align *beg = my_malloc(nobj * nbytes);
    if (beg == NULL)
        return NULL;
    for (i = 0; i < nobj * nbytes; i++)
        beg[i] = 0;
    return (void *) beg;
}

#define NTEST 3

int main(int argc, char *argv[])
{
    char *all = (char *) my_calloc(NTEST, sizeof(char));
    int i;
    for (i = 0; i < NTEST; i++)
        printf("%d\n", all[i]);
    return 0;
}