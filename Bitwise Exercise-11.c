/* C program to flip all bits of a binary number 
 * https://codeforwin.org/2016/01/c-program-to-flip-all-bits-of-binary-number.html
 * Write a C program to input a number from user and flip all bits of the given number (in binary representation) using bitwise operator.
 */

#include <stdio.h>

int main(void)
{
	int num, newNum;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	newNum = ~num;
	
	printf("New value of %i after bit inversion: %i\n", num, newNum);
	
	return 0;
}

