#include <stdio.h>

int setbits(int x, int p, int n, int y);

main()
{
	printf ("%x", setbits('\x6b', 6, 4, '\xb2') );

	getchar();

	return 0;
}

int setbits(int x, int p, int n, int y)
{
	return ( ( ~( ( ~( (~0) <<n) ) << (p-n) ) ) & x) |
	( ( ( ~( (~0) << n) ) &y) << (p-n) );

/*
	a = ~a;
	a = a << n;
	a = ~a;
	a = a << (p-n);
	a = ~a;
	a = a & x;

	b = ~b;
	b = b << n;
	b = ~b;
	b = b & y;
	b = b << (p-n);

	return res;
*/
}


