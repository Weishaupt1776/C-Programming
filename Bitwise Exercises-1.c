/* C program to check Least Significant Bit (LSB) of a number is set or not 
 * https://codeforwin.org/2016/01/c-program-to-check-lsb-of-number.html
 * Write a C program to input any number from user and check whether the Least Significant Bit (LSB) of the given number is set (1) or not (0).
 */
 
 /* Weishaupt1776 */

#include <stdio.h>
#include "get.h"

int main(void)
{
	unsigned lsb = ~(~0 << 1);
	unsigned num; 
	
	printf("Enter any number: ");
	scanf("%i", &num);
	lsb &= num;
	
	if(lsb == 1)
	{
		printf("LSB of %i is set: (%i)\n", num, lsb);
	}
	else 
	{
		printf("LSB of %i is not set: (%i)\n", num, lsb);
	}
	
	return 0;
}

