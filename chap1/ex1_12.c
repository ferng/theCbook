#include <stdio.h>

main()
{

	int c;

	while ((c = getchar()) != EOF ){
		if (c == '\t' || c == ' ')
			putchar('\n');
		else
			putchar(c);
	}

	return(0);
}