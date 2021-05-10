/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Rewrite  the temperature
 * conversion program of Section 1.2 to use a function for conversion.
 */
 
#include <stdio.h>

float fahr_to_celsius(float fahrenheit);
float celsius_to_fahr(float celsius);

/* print Fahrenheit-Celsius table
 * for Fahr = 0, 20, ..., 300 */

int main(void)
{
	float fahr, celsius;
	int lower, upper, step;
	
	lower = 0;
	upper = 300; 
	step = 20;
	
	fahr = lower;
	celsius = fahr_to_celsius(fahr);
	
	printf("Fahrenheit to Celsius:\n"); // prints a table header
	while(fahr <= upper)
	{
		printf("%6.2f\t%6.2f\n", fahr, celsius); // prints table
		fahr += step; // increments fahr count by 20
		celsius = fahr_to_celsius(fahr);
	}
	
	return 0;
}

float fahr_to_celsius(float fahrenheit)
{
	float conversion_factor = 5.0 / 9.0;
	float converted_temperature = (fahrenheit - 32.0) * conversion_factor;	
	return converted_temperature;
}

float celsius_to_fahr(float celsius)
{
	float conversion_factor = 5.0 / 9.0;
	float converted_temperature = (celsius * conversion_factor) + 32.0;
	return converted_temperature;
}
