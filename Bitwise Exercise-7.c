/* C program to get highest order set bit of a number
 * https://codeforwin.org/2016/01/c-program-to-get-highest-order-set-bit-of-number.html
 * Write a C program to input any number from user and find highest order set bit of given number using bitwise operator.
 */

#include <stdio.h>

int main(void)
{
	int num, value;
	int bitlen = 0;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	
	while(num != 0)
	{
		num >>= 1;
		bitlen++;
	}
	
	if(bitlen == 0)
	{
		printf("Error: there are no bits in given number\n");
		return 0;
	}
	else
	{
		value = 1;
		value <<= bitlen-1;
		printf("The highest order set bit is %i: evaluated as %i\n", bitlen-1, value);
	}
	return 0;
}

