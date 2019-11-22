#include <stdio.h>
#include <limits.h>
#include <float.h>

main()
{
	int i;
	long double j;

	j = i = 0;

	printf("these are the values defined in headers, together with proof:\n");

	printf("\nchar          : %d\n\n", CHAR_BIT);

	for (i = 1 ; i <= INT_MAX && i > 0; i *= 2)
		printf("\t%d", i);
	printf("\nint           : %d\n", INT_MAX);

	printf("\nunsigned int  : %u\n", UINT_MAX);
	printf("\nshort int     : %d\n", SHRT_MAX);
	printf("\nlong int      : %u\n", LONG_MAX);
	printf("\nfloat         : %f\n\n", FLT_MAX);

/*	for (j = 1; j > 0; j *= 2)
		printf("\t%Le", j);    */
	for (j = 1; j > 0; j /= 2)
		printf("\t%Le", j);
	printf("\ndouble        : %f\n", DBL_MAX);

	printf("\nlong double   : %f\n", LDBL_MAX);

	getchar();
	return 0;
}
