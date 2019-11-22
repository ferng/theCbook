#include "syscalls.h"
#include <fcntl.h>

#define PERMS 0666

FILE *fopen(char *name, char *mode);
int fclose(FILE *fp);
int fflush(FILE *fp);

void filecopy(FILE *ifp, FILE *ofp);

main(int argc, char *argv[])
{
	FILE *fp;
	void filecopy(FILE *, FILE *);

	if (argc == 1)
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL)
				return 1;
			else{
				filecopy(fp, stdout);
				fflush(stdout);
				fclose(fp);
			}
	return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
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
