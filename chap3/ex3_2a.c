#include <stdio.h>

main()
{

	int c;

	while ((c = getchar()) != EOF ){
		switch (c) {
			case '\t':
				printf("\\t");
				break;
			case '\\':
				printf("\\\\");
				break;
			case '\n':
				printf("\\n\n");
				break;
			case 8:
				printf("\\b");
				break;
			default:
				putchar(c);
				break;
		}

	}

	return 0;
}
