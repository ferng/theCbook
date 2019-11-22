#include <stdio.h>

main()
{
	int c, nl, tb, sp;
	nl=0;
	tb=0;
	sp=0;

	while ((c = getchar()) != EOF ){
		if (c == '\n')
			++nl;
		if (c == '\t')
			++tb;
		if (c == ' ')
			++sp;
	}

	printf("\nnewlines=%d\ttabs=%d\tspaces=%d\n", nl, tb, sp);
	return 0;
}