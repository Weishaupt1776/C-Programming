/* C program to get lowest order or first set bit of a number 
 * https://codeforwin.org/2016/01/c-program-to-get-lowest-order-set-bit-of-number.html
 * Write a C program to input any number from user and find lowest order set bit of given number using bitwise operator.
 */

#include <stdio.h>

int main(void)
{
	int num, lowBit = 1, bitPosition = 0;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	
	if(num == 0)
	{
		printf("Error: there is no value input that have bits\n");
		return 0;
	}
	else
	{
		
		while((lowBit&num) == 0)
		{
			bitPosition++;
			lowBit <<= 1;
		}
		printf("Lowest order set bit is %i: evaluated as %i\n", bitPosition, lowBit);
		return 0;
	}
	
	return 0;
}

