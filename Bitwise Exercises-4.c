/* C program to set nth bit of a number 
 * https://codeforwin.org/2016/01/c-program-to-set-nth-bit-of-number-using-bitwise-operator.html
 * Write a C program to input any number from user and set nth bit of the given number as 1.
 */

#include <stdio.h>
#include "get.h"

int bitlen(unsigned d);

int main(void)
{
	int num, n, numBitlen;
	printf("Please enter any number: ");
	scanf("%i", &num);
	printf("Please enter n'th bit to set: ");
	scanf("%i", &n);
	numBitlen = sizeof(num) * 8;
	
	if(n > (numBitlen-1))
	{
		printf("Error: invalid <n'th bit>\n");
		return 0;
	}
	else
	{
		int bitmask = ~(~0 << 1);
		bitmask <<= n;
		num |= bitmask;
		printf("New value after setting the n'th bit: %i\n", num);
		printf("Binary representation of %i: ", num);
		decToBinary(num);
	}
	return 0;
}

