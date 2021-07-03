/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. There is no error
 * checking in day_of_year or month_day. Remedy this effect.
 */

/* The solution to this problem just consists of making sure that
 * the parameters entered are valid, e.g. there is no -1 month! 
 * The idea to implement this error checking is absolute, and therefore
 * the solution is rigid so I am borrowing the solution of this simple
 * problem from another programmer. Credit is given!
 * 
 * This solution is borrowed from Lars Wirzenius from penti.org */
 
 /* https://penti.org/~sederlok/misc/lang/c/the_c_programming_language_-_exercises/krx508.html
  * Lars Wirzenius's solution linked above */

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

	return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	
	/* checks if year, month, and day are valid parameters */
	if (year < 1900 || month < 1 || month > 12 || day < 1)
		return -1;
	
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	/* checks if day variable does not exceed days in ascribed month */
	if (day > daytab[leap][month])
		return -1;
		
	for (i = 1; i < month; i++) /* calculates day of year */
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	
	/* checks if year and yearday are valid parameters */
	if (year < 1900 || yearday < 1)
		return -1;
	
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	
	/* checks to make sure yearday variable does not exceed standard days of year */
	if ((leap && yearday > 366) || (!leap && yearday > 365))
		return -1;
		
	for (i = 1; yearday > daytab[leap][i]; i++) /* calculates month and day */
		yearday -= daytab[leap][i];
		
	*pmonth = i;
	*pday = yearday;
	
	return 0;
}
