#include <stdio.h>

int tolower(int c);

main()
{
	printf ("\nchar:%c\n", tolower('F') );

	getchar();

	return 0;
}

int tolower(int c)
{
	(c >= 'A' && c <='Z') ? c += 'a' - 'A' : 'c';

	return c;
}
