/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to 
 * print the corresponding Celsius to Fahrenheit table.
 */ 
 
#include <stdio.h>
 
int main(void)
{
	float fahr, celsius;
	int lower, upper, step;
	
	upper = 300;
	step = 20;
	
	printf("Celsius to Fahrenheit:\n");
	
	for(lower = 0; lower <= upper; lower += step)
	{
		celsius = lower;
		fahr = (celsius * (9.0/5.0) + 32.0);
		printf("%6.1f %6.1f\n", celsius, fahr);
	}
	
	return 0;
}
