/* compare two files, printing the first line where they differ */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE		80

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char *prog = argv[0], str1[MAXLINE], str2[MAXLINE];
	int line1 = 0, line2 = 0;

	if (argc != 3)
		fprintf(stderr, "error: %s: two files!, TWO FILES!!\n", prog);
	else {
		if ((fp1 = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "error: %s: can't open %s\n", prog, argv[1]);
			exit(1);
		}	else if ((fp2 = fopen(argv[2], "r")) == NULL) {
			fprintf(stderr, "error: %s: can't open %s\n", prog, argv[2]);
			exit(1);
		}	else {
			while (1 == 1) {
				fgets(str1, MAXLINE, fp1);
				line1++;
				fgets(str2, MAXLINE, fp2);
				line2++;

				if (feof(fp1) && feof(fp2))		/* both at eol */
					break;
				if (feof(fp1)) {
					printf("%s %d: %s\n", argv[2], line2, str2);
					break;
				}
				if (feof(fp2)) {
					printf("%s %d: %s\n", argv[1], line1, str1);
					break;
				}
				if (strcmp(str1, str2) != 0) {
					printf("%s %d: %s\n", argv[1], line1, str1);
					printf("%s %d: %s\n", argv[2], line2, str2);
					break;
				}
			}
		}
	}

	if (ferror(stdout)) {
		fprintf(stderr, "error: %s: error writing stdout\n", prog);
		exit(2);
	}
	exit(0);
}
