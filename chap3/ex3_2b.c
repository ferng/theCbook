#include <stdio.h>

#define MAXLINE		40

void makeInvisible(char input[], char output[]);

main()
{
	char input[MAXLINE], output[MAXLINE];

	input[0]='h';
	input[1]='e';
	input[2]='l';
	input[3]='o';
	input[4]='\\';
	input[5]='t';
	input[6]='h';
	input[7]='o';
	input[8]='w';
	input[9]=' ';
	input[10]='a';
	input[11]='r';
	input[12]='e';
	input[13]=' ';
	input[14]='y';
	input[15]='o';
	input[16]='u';
	input[17]='\0';

	makeInvisible(input, output);
	printf("\nconverted line: %s\n", output);

	return 0;
}


void makeInvisible(char input[], char output[])
{
	int i=0, j=0;
	char c;

	while ((c=input[i++]) != '\0'){
		if ((c == '\\') && (input[i] != '\0')){
			c = input[i++];

			switch (c) {
				case 't':
					output[j++] = '\t';
					break;
				case '\\':
					output[j++] = '\\';
					break;
				case '\n':
					output[j++] = '\n';
					break;
				case 8:
					output[j++] = '\b';
					break;
				default:
					output[j++] = c;
					break;
			}
		}
		else{
			output[j++] = c;
		}

	}
	output[j] = '\0';

}
