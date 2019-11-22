#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_of_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
	int month, day, doy;

	doy = day_of_year(2008, 3, 1);
	if (doy > -1)
		printf("\non leap years 1st March is the %dth day of the year",doy);

	doy = day_of_year(2009, 3, 1);
	if (doy > -1)
		printf("\non non-leap years 1st March is the %dth day of the year",doy);

	doy = month_of_day(2008, 60, &month, &day);
	if (doy > -1)
		printf("\non leap years the 60th day is the %d day of the %d month", day, month);

	doy = month_of_day(2009, 60, &month, &day);
	if (doy > -1)
		printf("\non non-leap years the 60th day is the %d day of the %d month", day, month);

	return 0;
}

int day_of_year(int year, int month, int day)
{
	int i, leap;
	char *monDayPtr;

	if (year < 0 || month < 0 || day < 0)
		return -1;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	monDayPtr = &daytab[0][0];

	if (day > *(monDayPtr+((leap*13)+month)))
		return -1;

	for (i = 1; i < month; i++)
		day += *(monDayPtr+((leap*13)+i));

	return day;

}

int month_of_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	char *monDayPtr;

	if (year < 0 || yearday < 0)
		return -1;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	monDayPtr = &daytab[0][0];
	
	if ((yearday - leap) > 365)
		return -1;

	for (i = 1; yearday > *(monDayPtr+((leap*13)+i)); i++)
		yearday -= *(monDayPtr+((leap*13)+i));
	*pmonth = i;
	*pday = yearday;

	return 0;
}
