#include <stdio.h>

int bitcount(short unsigned int x);

main()
{
	printf ("\nones:%d\n", bitcount('\xb5') );

	getchar();

	return 0;
}

int bitcount(short unsigned int x)
{
	int b, clearer;
	
	clearer = ~( (~0) << 7);
	
	x &= 0xff;

	for (b = 0; x != 0; x >>= 1)
	{
		b += (x & 0x01);
	}

	return b;
}
