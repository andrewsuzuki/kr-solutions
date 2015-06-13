/*
 * Filename:    malloc-safer.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/12/2015
 *
 * Exercise 8-7. malloc accepts a size request without checking its plausibility;
 * free believes that the block it is asked to free contains a valid size field.
 * Improve these routines so they take more pains with error checking.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
 
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

    if (ap == NULL)
        return;

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

    if (nbytes == 0)
        return NULL;

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

int main(int argc, char *argv[])
{
    assert(my_malloc(0) == NULL);
    assert(my_malloc(1) != NULL);
    return 0;
}