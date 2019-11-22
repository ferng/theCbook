#include <stdio.h>

main()
{
	int c, eofTest;

	while (eofTest = ((c = getchar()) != EOF)){
		putchar(c);
		printf("\tThe value of getchar()!=EOF is: %d\n", eofTest);
	}

	printf("\tThe value of getchar()!=EOF is: %d\n", eofTest);
	printf("EOF value = %d\n", c );
	return 0;
}