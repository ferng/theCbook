#include <stdio.h>

main()
{

	int c;

	while ((c = getchar()) != EOF ){
		if (c != '\t')
			if (c != 8)
				if (c != '\\')
					putchar(c);

		if (c == '\t')
			printf("\\t");
		if (c == 8)
			printf("\\b");
		if (c == '\\')
			printf("\\\\");
	}

	return 0;
}
