/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Rewrite the routines
 * day_of_year and month_day with pointers instead of indexing.
 */

/* The solution can be arrived at with ease without altering the code
 * in any significant way */

/* Credit goes to Larz Wirzenius for the inspired solution 
 * https://penti.org/~sederlok/misc/lang/c/the_c_programming_language_-_exercises/krx509.html */

#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = 
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void)
{
	int month, day, yearday;
	month = day = 1;
	yearday = day_of_year(2021, 7, 3);
	month_day(2021, 184, &month, &day);
	printf("Day of year: %i\n", yearday);
	printf("Day of month: %i/%i/2021\n", month, day);
	return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	char *p;
	
	/* checks if year, month, and day are valid parameters */
	if (year < 1900 || month < 1 || month > 12 || day < 1)
		return -1;
	
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	p = &daytab[leap][1];

	/* checks if day variable does not exceed days in ascribed month */
	if (day > *p + (month-1))
		return -1;
		
	for (i = 1; i < month; i++, p++) /* calculates day of year */
		day += *p;
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	char *p;
	
	/* checks if year and yearday are valid parameters */
	if (year < 1900 || yearday < 1)
		return -1;
	
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	p = &daytab[leap][1];
	
	/* checks to make sure yearday variable does not exceed standard days of year */
	if ((leap && yearday > 366) || (!leap && yearday > 365))
		return -1;
		
	for (i = 1; yearday > *p; i++, p++) /* calculates month and day */
		yearday -= *p;
		
	*pmonth = i;
	*pday = yearday;
	
	return 0;
}
