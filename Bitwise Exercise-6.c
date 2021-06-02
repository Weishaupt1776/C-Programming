/* C program to toggle or invert nth bit of a number
 * https://codeforwin.org/2016/01/c-program-to-toggle-nth-bit-of-number.html
 * Write a C program to input any number from user and toggle or invert or flip nth bit of the given number using bitwise operator
 */

#include <stdio.h>

int main(void)
{
	int num, n, newNum;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	printf("Enter the n'th bit to toggle: ");
	scanf("%i", &n);
	
	if(n > (sizeof(num) * 8))
	{
		printf("Error: invalid n'th bit\n");
		return 0;
	}
	else
	{
		newNum = (1 << n);
		newNum ^= num;
		printf("The new value number: %i", newNum); 
	}
	
	return 0;
}

