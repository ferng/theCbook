#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#define	MAXLENIN		300
#define	MAXWORD			20

void minscanf(char *fmt, ...);

main()
{
	int iVal;
	double dVal;
	char sVal[MAXWORD];

	minscanf("%d%f%s", &iVal, &dVal, sVal);
	printf("so, we got this: %s, %d, %f\n", sVal, iVal, dVal);
	
	return 0;
}

void minscanf(char *fmt, ...)
{
	va_list ap;
	char c, *p, *psval;
	int w, *pival;
	double *pdval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++){
		if (*p != '%'){
			continue;
		}

		switch (*++p){
		case 'd':
			pival = va_arg(ap, int *);
			scanf("%d", pival);
			break;
		case 'f':
			pdval = va_arg(ap, double *);
			scanf("%lf", pdval);
			break;
		case 's':
			psval = va_arg(ap, char *);
			scanf("%s", psval);
			break;
		}
	}
	va_end(ap);
}

