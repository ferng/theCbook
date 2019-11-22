#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#define	MAXLENIN		300

void minprintf(char *fmt, ...);

main()
{
	minprintf("%s, %9d, %f, %x, %p\n", "hello ", 7, 3.42, 565.67, "what about");
	return 0;
}

void minprintf(char *fmt, ...)
{
	va_list ap;
	char c, *p, *sval;
	int w, ival;
	double dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++){
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		if (isdigit(c = w = *++p)){
			c = *++p;
		}
		switch (c){
		case 'd':
			ival = va_arg(ap, int);
			if (isdigit(w))
				printf("%*d", w-48, ival);
			else
				printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 'x':
			dval = va_arg(ap, double);
			printf("%x", dval);
			break;
		case 'p':
			dval = va_arg(ap, double);
			printf("%s", "prrp");
			break;
		case 's':
			for (sval = va_arg(ap, char*); *sval; sval++)
				putchar(*sval);
			break;
		}
	}
	va_end(ap);
}

