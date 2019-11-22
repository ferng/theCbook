#include <stdio.h>

int binSearch(int x, int v[], int n);

main()
{
	int x, v[7];

	v[0]=1;		v[1]=2;		v[2]=5;		v[3]=6;		v[4]=7;		v[5]=9;		v[6]=10;

	x = binSearch(3, v, 7);

	if (x == -1)
		printf ("\nno match found dude");
	else
		printf ("\nmatch found in element %d", x);

	return 0;

}

int binSearch(int x, int v[], int n)
{
	int low, mid, high;

	mid = low = 0;
	high = n - 1;

	while ( x != v[mid] && low <= high){
		mid = (low + high) / 2;

		if (x > v[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}

	if (x == v[mid])
		return mid;
	else
		return -1;
}
