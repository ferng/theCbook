#include <stdio.h>

main()
{
	int c, i, freq;
	int	cFreq[26];

	c = i = freq = 0;
	for (i = 0; i < 26; ++i)
		cFreq[i] = 0;

	while ((c = getchar()) != EOF){
		cFreq[c-'a']++;
	}

	for (freq = 9; freq >= 0; --freq){
		for (i = 0; i < 26; ++i){
			if (cFreq[i] > freq)
				putchar('*');
			else
				putchar(' ');
		}
		printf("\n%d",freq);
	}

	printf("\n ");
	for (i = 0; i < 26; ++i)
		putchar(i+'a');

	getchar();
	return 0;
}