#include "syscalls.h"
#include <fcntl.h>

#define PERMS 0666

FILE *fopen(char *name, char *mode);

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
/*				fclose(fp); */
			}
	return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c, i;
	char buf[1];

	while ((c = getc(ifp)) != EOF){ 
/*		putc(c, ofp);	*/
		buf[0] = c;
		write(1, buf, 1);		
	}
}

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode !='w' && *mode !='a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->fRead == 0) && (fp->fWrite == 0))
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
	if (*mode == 'r'){
		fp->fRead = 1;
		fp->fWrite = 0;
	} else {
		fp->fRead = 0;
		fp->fWrite = 1;
	}
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (fp->fRead == 0 || fp->fEof == 1 || fp->fError == 1)
		return EOF;
	if (fp->fUnbuf == 0)
		bufsize = 1;
	else
		bufsize = BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->fEof = 1;
		else
			fp->fError = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}
