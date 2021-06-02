/* C program to count zeros and ones in a binary number 
 * https://codeforwin.org/2016/01/c-program-to-count-number-of-ones-and-zeros-in-binary-number.html
 * Write a C program to input a number from user and count total number of ones (1s) and zeros (0s) in the given number using bitwise op.
 */

#include <stdio.h>

int main(void)
{
	int num, totalZeros, totalOnes, bits;
	
	
	printf("Enter any number: ");
	scanf("%i", &num); 
	bits = sizeof(num) * 8;
	totalOnes = totalZeros = 0;
	
	for(int i = 0; i < bits; i++)
	{
		if(((1 << i) & num) == 0)
		{
			totalZeros++;
		}
		else
		{
			totalOnes++;
		}
	}
	
	printf("Total output 1 bits: %i\n", totalOnes);
	printf("Total output 0 bits: %i\n", totalZeros);
	return 0;
}

