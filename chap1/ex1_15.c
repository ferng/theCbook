#include <stdio.h>

float toFahr(int cel);

main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 150;
	step = 10;

	printf("celsius  fahrenheit\n");
	celsius = lower;
	while (celsius <= upper){
		fahr =  toFahr(celsius);
		printf ("%7.0f %11.1f   :-)\n", celsius, fahr);
		celsius = celsius + step;
	}
	getchar();
	return 0;
}

float toFahr(int cel)
{
	return ((9.0/5.0) * cel)+32.0;
}