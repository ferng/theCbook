#include <stdio.h>
#include <ctype.h>
#include <string.h>

main(int argc, char *argv[])
{
	int c, conv = 0;

	if (strcmp(argv[0], "./DOWNS") == 0)
		conv = 1;

	while((c = getchar()) != EOF){
		if (conv == 0)
			putchar(toupper(c));
		else
			putchar(tolower(c));
	}
	return 0;
}
