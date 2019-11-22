#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE		70

int main(int argc, char *argv[])
{
	FILE *fp;
	char line[MAXLINE], header[79], pad[40];
	int pageNo, lineNo, padSize, i;

	while (*++argv != NULL) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			fprintf(stderr, "error: can't open %s\n", *argv);
			exit(1);
		}
		pageNo = lineNo = 1;
		sprintf(header, "New File: %s", *argv);
		padSize = ((80 - strlen(header)) / 2) - 2;
		for (i = 0; i < padSize; i++)
			pad[i] = '-';
		pad[i] = '\0';
		printf ("%s %s %s\n", pad, header, pad);

		while (fgets(line, MAXLINE, fp) != NULL) {
			if (lineNo == 64) {
				sprintf(header, "%s - page: %3d", *argv, pageNo);
				padSize = ((80 - strlen(header)) / 2) - 2;
				for (i = 0; i < padSize; i++)
					pad[i] = '-';
				pad[++i] = '\0';
				printf ("\n%s %s %s\n\n", pad, header, pad);

				lineNo = 1;
				pageNo++;
			}
			printf("%s", line);
			lineNo++;
		}
		sprintf(header, "%s - page: %3d", *argv, pageNo);
		padSize = ((80 - strlen(header)) / 2) - 2;
		for (i = 0; i < padSize; i++)
			pad[i] = '-';
		pad[++i] = '\0';
		printf ("\n%s %s %s\n\n", pad, header, pad);
	}
	exit(0);
}

