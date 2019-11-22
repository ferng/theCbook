#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void procLine(char line[], char dropList[]);

main()
{
	char line[MAXLINE], dropList[MAXLINE];

	dropList[0] = 'a';
	dropList[1] = 'e';
	dropList[2] = 'i';
	dropList[3] = 'o';
	dropList[4] = 'u';
	dropList[5] = '\0';

	while (getline(line, MAXLINE) > 0){
		printf("orig: %s", line);
		procLine(line, dropList);
		printf("proc: %s", line);
	}
	getchar();
	return 0;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';

	return i;
}

void procLine(char line[], char dropList[])
{
	int i=0, j=0, dropPos;
	char d;

	while (line[i] != '\0'){
		dropPos=0;
		while ( (d=dropList[dropPos]) != '\0' && line[i] != d)
			dropPos++;

		if (d == '\0')		/* reached the end of chars to drop so we can copy */
			line[j++] = line[i];

		i++;
	}

	line[j] = '\0';
	return;
}
