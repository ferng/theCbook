#include <stdio.h>

main()
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 150;
	step = 10;

	printf("fahrenheit  celsius\n");
	fahr = lower;
	while (fahr <= upper){
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%10.0f %8.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return 0;
}