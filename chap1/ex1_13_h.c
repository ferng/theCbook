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

	for (i = 0; i < 9; ++i){
		for (j = 0; j < wLen[i]; j++)
			putchar('*');
		printf("\n%d ",i+1);
	}

	return 0;
}