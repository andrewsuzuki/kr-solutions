/*
 * Filename:	doty-ptr.c
 * Author:		Andrew Suzuki <andrew.b.suzuki@gmail.com>
 * Date:		06/04/2015
 *
 * Exercise 5-9. Rewrite the routines day_of_year and month_day with
 * pointers instead of indexing.
 */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int is_leap_year(int year) {
	return (year%4 == 0 && year%100 != 0) || year%400 == 0;
}

int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = is_leap_year(year);

	if (month < 1 || month > 12 || *(*(daytab + leap) + month) < day)
		return -1;

	for (i = 1; i < month; i++)
		day += *(*(daytab + leap) + i);

	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = is_leap_year(year);

	if (year < 0 || yearday <= 0 || yearday > ((leap) ? 366 : 365))
		return -1;

	for (i = 1; yearday > *(*(daytab + leap) + i); i++)
		yearday -= *(*(daytab + leap) + i);

	*pmonth = i;
	*pday = yearday;

	return 0;
}

int main() {
	int month, day;

	printf("%d -- ", month_day(2015, 154, &month, &day)); /* 0 */
	printf("%d -- %d\n", month, day); /* 6 -- 3 */

	printf("%d\n", month_day(2015, 366, &month, &day)); /* -1 */
	printf("%d -- ", month_day(2016, 366, &month, &day)); /* 0 (leap year) */
	printf("%d -- %d\n", month, day); /* 12 -- 31 */

	printf("%d\n", day_of_year(2015, 6, 3)); /* 154 */
	printf("%d\n", day_of_year(2016, 6, 3)); /* 155 (leap year) */
	printf("%d\n", day_of_year(2015, 2, 29)); /* -1 (bad date) */
	printf("%d\n", day_of_year(2016, 2, 29)); /* 60 (leap year) */
}