#include <stdio.h>

#define swap(t,x,y)		{ t tmp; tmp=x; x=y; y=tmp; }

int main()
{
	int a = 1, b = 2;
	char c = 'c', d = 'd';

	swap(int,a,b);
	printf("a=%d b=%d\n",a,b);

	swap(char,c,d);
	printf("c=%c d=%c\n",c,d);

	return 0;
}
