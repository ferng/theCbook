#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void filecopy(int ifp, int ofp);

int main(int argc, char *argv[])
{
	int fd;
	char *prog = argv[0];

	if (argc == 1)
		filecopy(0, 1);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				fprintf(stderr, "error: %s: can't open %s\n", prog, *argv);
				exit(1);
			}	else {
				filecopy(fd, 0);
				close(fd);
			}
	exit(0);
}

void filecopy(int ifp, int ofp)
{
	char c[1];
	int n;

	while ((n = read(ifp, c, 1)) > 0)
		write(ofp, c, 1);
}
