#include <stdio.h>

main()
{
	int c, sp;

	sp = 0;

	while ((c = getchar()) != EOF ){
		if (c != ' '){
			putchar(c);
			sp = 0;
		}
		if (c == ' '){
			if (sp == 0)
			putchar(c);
			sp = 1;
		}
	}

	return 0;
}