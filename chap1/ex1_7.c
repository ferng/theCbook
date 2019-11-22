#include <stdio.h>

main()
{
	int c;
	while ((c = getchar()) != EOF)
	putchar(c);
	printf("EOF value = %d\n", c );
	return 0;
}