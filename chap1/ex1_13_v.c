#include <stdio.h>

main()
{
	int c, i, j, curLen;
	int	wLen[9];

	c = i = curLen = 0;
	for (i = 0; i < 9; ++i)
		wLen[i] = 0;

	while ((c = getchar()) != EOF){
		curLen++;
		if (c == ' ' || c == '\t' || c == '\n'){
			wLen[curLen-1]++;
			curLen = 0;
		}
	}

	for (i = 9; i >= 0; --i){
		for (j = 0; j < 9; ++j){
			if (wLen[j] > i)
				putchar('*');
			else
				putchar(' ');
		}
		printf("\n%d",i);
	}

	printf("\n ");
	for (i = 0; i < 9; ++i)
		putchar(i+'0');

	getchar();
	return 0;
}