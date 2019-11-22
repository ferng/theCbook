#include <stdio.h>

#define MAXLINE 20
#define FALSE 0
#define TRUE 1

int		getLine(char s1[], int maxLen);

void	expand(char s1[], char s2[]);

main()
{
	char s1[MAXLINE], s2[MAXLINE];

	while (getLine(s1, MAXLINE) != EOF){
		expand(s1,s2);
		printf("expanded: %s\n", s2);
	}

	return 0;
}	


int getLine(char s1[], int maxLen){
	int i=0;
	char c;

	while ((c=getchar()) != EOF && c!= '\n' && i <= maxLen-1)
		s1[i++] = c;

	s1[i] = '\0';
		
	if (c == EOF)
		return EOF;
	else
		return i;
}


void expand(char s1[], char s2[])
{
	int start=0, end, offset=0, i, outPos;

	if (s1[start] == '-'){
		offset = 1;
		s2[start++] = '-';
	}

	while (s1[start] != '\0'){

		end = start+2;

		for (i = s1[start]; i <= s1[end]; i++){
			outPos = i-s1[start]+offset;
			s2[outPos] = i;
		}

		offset = i-s1[start]+offset;
		start = (s1[end+1] == '-') ? end : end+1;
	}
	
	s2[outPos+1] = '\0';

	return;
}
