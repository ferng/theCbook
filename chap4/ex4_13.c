#include <stdio.h>

void reverse(char s[]);

int main()
{
	char s[] = "ab";

	reverse(s);
	printf("%s",s);
	return 0;
}

void reverse(char s[])
{
	static int end = 0;
	static int start = 0;

	char tmp;

	if (end == 0)
		end = strlen(s) -1 ;
	
	tmp = s[start];
	s[start] = s[end];
	s[end] = tmp;

	start++;
	end--;

	if (end > start)
		reverse(s);
}

