#include <ctype.h>
#include <stdio.h>

int main()
{
	char c;
	int count = 0;

	while ((c = getc(stdin)) != EOF){
		if (c >= 'A' && c <= 'Z')
			count++;
	}
	printf("this many: %d\n", count);
	return 0;
}
