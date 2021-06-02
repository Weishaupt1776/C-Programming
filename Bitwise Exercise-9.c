/* C program to count trailing zeros in a binary number 
 * https://codeforwin.org/2016/01/c-program-to-count-trailing-zeros-in-binary-number-using-bitwise-operator.html
 * Write a C program to input any number from user and count number of trailing zeros in the given number using bitwise operator.
 */

#include <stdio.h>
#include "get.h"

int main(void)
{
	int num, count = 0;
	scanf("%i", &num);

	while(((num>>count) & 1) == 0)
		count++;
		
	printf("Trailing blanks in %i: %i\n", num, count);
	
	return 0;
}

