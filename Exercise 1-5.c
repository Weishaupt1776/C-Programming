/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Modify the temperature
 * conversion program to print the table in reverse order, that is,
 * from 300 degrees to 0.
 */

#include <stdio.h>
 
int main(void)
{
	float fahr, celsius;
	int lower, upper, step;
	
	lower = 0;
	step = 20;
	
	printf("Celsius to Fahrenheit:\n");
	
	for(upper = 300; upper >= lower; upper -= step)
	{
		celsius = upper;
		fahr = (celsius * (9.0/5.0) + 32.0);
		printf("%6.1f %6.1f\n", celsius, fahr);
	}
	
	return 0;
}
