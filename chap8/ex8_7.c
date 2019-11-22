#include "syscalls.h"
#include <fcntl.h>

#define PERMS 0666
#define NALLOC 16
#define MAXALLOC	NALLOC*16

FILE *fopen(char *name, char *mode);
int fclose(FILE *fp);
int fflush(FILE *fp);
int fseek(FILE *fp, long offset, int origin);
int _fillbuf(FILE *fp);
int _flushbuf(int c, FILE *fp);
void *malloc(unsigned nbytes);
void free(void *ap);
Header *morecore(unsigned nu);

void filecopy(FILE *ifp, FILE *ofp);

static Header base;
static Header *freep = NULL;

main(int argc, char *argv[])
{
	int c;
	FILE *fp;

	if (argc == 1)
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL)
				return 1;
			else{
				fseek(fp, 0, 0);
				filecopy(fp, stdout);
				fflush(stdout);

				fseek(fp, 6, 0);
				filecopy(fp, stdout);
				fflush(stdout);

				fclose(fp);
			}
	return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c, i;
	while ((c = getc(ifp)) != EOF){ 
		putc(c, ofp);
	}
}

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode !='w' && *mode !='a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp>= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else
		fd = open(name, O_RDONLY, 0);

	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE; 
	return fp;
}

int fclose(FILE *fp)
{
	if (fp->flag & _WRITE);
		fflush(fp);
	close(fp->fd);
}

int fflush(FILE *fp)
{
	_flushbuf(EOF, fp);
}

int fseek(FILE *fp, long offset, int origin)
{
	if (fp->flag & _WRITE)
		fflush(fp);
	if (fp->flag & _READ){
	fp->flag = ( ~(_EOF | _ERR)) & fp->flag;
		fp->cnt = 0;
	}

	lseek(fp->fd, offset, origin) >= 0;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
 	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
	char buf[1];

	if (!(fp->flag & _UNBUF)){
		if (fp->base == NULL)
			if ((fp->base = (char *) malloc(BUFSIZ)) == NULL)
				return EOF;
		fp->ptr = fp->base;
		write(fp->fd, fp->ptr, (BUFSIZ - fp->cnt));
		fp->cnt = BUFSIZ;
	}
	if (c != EOF){
		buf[0] = c;
		write(1, buf, 1);
	}
}

void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;

	if (nbytes+sizeof(Header)-1 > MAXALLOC)
		return NULL;

	nunits = (nbytes+sizeof(Header)-1) / sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

Header *morecore(unsigned nu)
{
	char *cp, *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up+1));
	return freep;
}

void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;
	if (bp->s.size <= MAXALLOC){
		for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
			if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
				break;

		if (bp + bp->s.size == p->s.ptr){
			bp->s.size += p->s.ptr->s.size;
			bp->s.ptr = p->s.ptr->s.ptr;
		} else
			bp->s.ptr = p->s.ptr;

		if (p + p->s.size == bp) {
			p->s.size += bp->s.size;
			p->s.ptr = bp->s.ptr;
		} else
			p->s.ptr = bp;
		freep = p;
	}
}
