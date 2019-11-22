#include <stdio.h>

int rightrot(int x, int n);

main()
{
	printf ("%x", rightrot('\x6b', 3) );

	getchar();

	return 0;
}

int rightrot(int x, int n)
{
	int i, clearer, getter, bitToMove;

	clearer = ~( (~0) << 7);	/* only rightmost bit is a 0. & to clear it */
	getter = 1;		/* left most bit is 1. | & to pick out what x has there */

	for (i = 1; i <= n; i++){
		bitToMove = (x & getter) << 7 ; /* got the bit and moved it  */
		x = x >> 1;											/* make room for the new bit */
		x = x & clearer;
		x = x | bitToMove;							/* right bit in left pos now */
	}

	return x;

}


