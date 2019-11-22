#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE		100

int main(int argc, char *argv[])
{
	FILE *fp;
	char line[MAXLINE], match[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
			case 'x':
				printf("except\n");
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("error: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}
		}
	}

	strcpy(match, *argv);
	if (*(argv+1) == 0){
		while (fgets(line, MAXLINE, stdin) != NULL) {
			lineno++;
			if ((strstr(line, match) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s\n", line);
				found++;
			}
		}
	}
	while (*++argv != NULL) {
		lineno = 0;
		if ((fp = fopen(*argv, "r")) == NULL) {
			fprintf(stderr, "error: can't open %s\n", *argv);
			exit(1);
		}
		while (fgets(line, MAXLINE, fp) != NULL) {
			lineno++;
			if ((strstr(line, match) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s: %s\n", *argv, line);
				found++;
			}
		}
	}
	exit(found);
}

