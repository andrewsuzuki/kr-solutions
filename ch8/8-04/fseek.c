/*
 * Filename:    fseek.c
 * Author:      Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:        06/11/2015
 *
 * Exercise 8-4. The standard library function
 *     int fseek(FILE *fp, long offset, int origin)
 * is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and the return value is an int status, not a position. Write
 * fseek. Make sure that your fseek coordinates properly with the buffering
 * done for the other functions of the library.
 *
 * ---
 * 
 * meh, only kinda sorta works. will fix.
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef NULL
#undef NULL
#endif

/* pg. 176 */

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

struct flags {
    unsigned read : 1;
    unsigned write : 1;
    unsigned unbuf : 1;
    unsigned eof : 1;
    unsigned err : 1;
};

typedef struct _iobuf {
    int cnt;        /* characters left */
    char *ptr;      /* next character position */
    char *base;     /* location of the buffer */
    struct flags ff;/* mode of the file access (flag bitfield) */
    int fd;         /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

FILE *fopen(char *name, char *mode);
int fflush(FILE *fp);
int fclose(FILE *fp);
int fseek(FILE *fp, long offset, int origin);
int _fillbuf(FILE *fp);
int _flushbuf(int, FILE *fp);

#define feof(p)     ((p)->ff.eof)
#define ferror(p)   ((p)->ff.err)
#define fileno(p)   ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->cnt > 0 && (x) != '\n' ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

FILE _iob[OPEN_MAX] = {     /* stdin, stdout, stderr */
        { 0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0 },
        { 0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1 },
        { 0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2 }
};

#define LINES_TO_TEST 3

int main(int argc, char *argv[])
{
    /* test for closing file, should seek to beginning after 5 lines */

    int c;
    int nlines = 1;
    FILE *opened = fopen("fseek.c", "r");

    while ((c = getc(opened)) != EOF) {
        putchar(c);
        if (nlines == LINES_TO_TEST) {
            fseek(opened, 1, 1);
        }
        if (c == '\n') nlines++;
    }
}

/* pg. 177 */

#define PERMS 0666

void reset_ff(struct flags *ff)
{
    ff->read = 0;
    ff->write = 0;
    ff->unbuf = 0;
    ff->eof = 0;
    ff->err = 0;
}

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->ff.read == 0 && fp->ff.write == 0)
            break; /* found free slot */
    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1) /* couldn't access name */
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;

    reset_ff(&(fp->ff));

    if (*mode == 'r')
        fp->ff.read = 1;
    else
        fp->ff.write = 1;

    return fp;
}

/* pg. 178 */

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (fp->ff.read == 0 || fp->ff.eof == 1 || fp->ff.err == 1)
        return EOF;

    bufsize = (fp->ff.unbuf == 1) ? 1 : BUFSIZ;

    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->ff.eof = 1;
        else
            fp->ff.err = 1;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

/* _flushbuf: flush (write) buffer, return characters written */
/* adapted and fixed from broken answer found on clcwiki.net */
int _flushbuf(int c, FILE *f) {
    int num_written, bufsize;
    unsigned char uc = c;

    if (f->ff.write == 0 || f->ff.eof == 1 || f->ff.err == 1) {
        return EOF;
    }

    if (f->base == NULL && f->ff.unbuf == 0) {
        /* no buffer yet */
        if ((f->base = malloc(BUFSIZ)) == NULL)
            /* could not allocate a buffer, so try unbuffered */
            f->ff.unbuf = 1;
        else {
            /* allocation worked, set ptr to beginning */
            f->ptr = f->base;
            f->cnt = BUFSIZ - 1; /* - 1 to make room for given c param */
        }
    }

    if (f->ff.unbuf) {
        /* unbuffered write */
        f->ptr = f->base = NULL;
        f->cnt = 0;
        if (c == EOF) {
            return EOF;
        }
        num_written = write(f->fd, &uc, 1);
        bufsize = 1;
    } else {
        /* buffered write */
        if (c != EOF) {
            *(f)->ptr = uc;
        } 
        bufsize = (int)(f->ptr - f->base + 1); /* +1 for current c */
        num_written = write(f->fd, f->base, bufsize);
        /* reset ptr to beginning and cnt to full */
        f->ptr = f->base;
        f->cnt = BUFSIZ - 1;
    }

    if (num_written == bufsize)
        return c;
    else {
        f->ff.err = 1;
        return EOF;
    }
}

/* forces write of output buffer / discards input buffer. If NULL, flush all output streams */
int fflush(FILE *fp)
{
    int i, ok;

    if (fp == NULL) {
        /* recursively flush each output buffer */
        ok = 0;
        for (i = 0; i < OPEN_MAX; i++)
            if ((_iob + i)->ff.write == 1 && fflush((_iob + i)) == EOF)
                ok = EOF;
        return ok;
    } else {
        if (fp->ff.write == 0)
            return EOF; /* only flush output streams */

        _flushbuf(EOF, fp); /* flush buffer */

        if (fp->ff.err == 1) /* check for errors */
            return EOF;

        return 0;
    }
}

int fclose(FILE *fp)
{
    int fd;

    if (fp == NULL)
        return EOF;

    fflush(fp);

    fd = fp->fd;
    fp->fd = 0;
    fp->cnt = 0;
    fp->ptr = NULL;
    /* free flags (important, this
    is how it determines if it can be reopened) */
    reset_ff(&(fp->ff));
    /* free buffer */
    if (fp->base != NULL)
        free(fp->base);
    fp->base = NULL;

    return close(fd);
}

/* fseek: seeks to offset from origin (0/1/2), returns 0 on success */
/* adapted from answer on clcwiki.net */
int fseek(FILE *fp, long offset, int origin)
{
    int res;

    if (fp->ff.unbuf == 0 && fp->base != NULL) {
        if (fp->ff.write) {
            if (fflush(fp))
                return EOF;
        } else if (fp->ff.read) {
            if (origin == 1) {
                if (offset >= 0 && offset <= fp->cnt) {
                    fp->cnt -= offset;
                    fp->ptr += offset;
                    fp->ff.eof = 0;
                    return 0;
                } else {
                    offset -= fp->cnt;
                }
            }
            fp->cnt = 0;
            fp->ptr = fp->base;
        }
    }
    res = (lseek(fp->fd, offset, origin) < 0);
    if (res == 0)
        fp->ff.eof = 0;
    return res;
}