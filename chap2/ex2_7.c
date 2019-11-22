#include <stdio.h>

int invert(int x, int p, int n);

main()
{
	printf ("%x", invert('\x6b', 6, 4) );

	getchar();

	return 0;
}

int invert(int x, int p, int n)
{


/*	int a, b, y, res;

	a = b = y = res = 0;

	y = (~(x >> (p-n)));
	a = ( (~( (~((~0) << n)) << (p-n) )) & x);
	b = (~((~0) << n) & y ) << (p-n);
*/

	return ( (~( (~((~0) << n)) << (p-n) )) & x) |
		(~((~0) << n) &	(~(x >> (p-n)))	) << (p-n);




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

	res = a | b ;

	return res;
*/

}


