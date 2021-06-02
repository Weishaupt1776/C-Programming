/* C program to clear nth bit of a number
 * https://codeforwin.org/2016/01/c-program-to-set-nth-bit-of-number-using-bitwise-operator.html
 * Write a C program to input any number from user and clear the nth bit of the given number using bitwise operator.
 */

#include <stdio.h>

int bitlen(unsigned d) ;

int main(void)
{
	int num, n, numBitlen;
	printf("Enter any number: ");
	scanf("%i", &num);
	printf("Enter the n'th bit to clear: ");
	scanf("%i", &n);
	numBitlen = bitlen(num);
	
	if(n > (numBitlen-1))
	{
		printf("Error: invalid n'th bit\n");
		return 0;
	}
	else
	{
		int bitmask = 1;
		bitmask <<= n;
		bitmask = ~bitmask;
		num &= bitmask;
		printf("New value of num is: %i", num);
	}
	
	return 0;
}

/* This function is borrowed from the user fool2fish on github
 * https://github.com/fool2fish/the-c-programming-language-exercise-answers/blob/master/ch02/2-6.c
 */
int bitlen(unsigned d) 
{
  int len = 0;
  for (; d; d >>= 1) {
    len++;
  }
  return len;
}

