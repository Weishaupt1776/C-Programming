/* C program to get nth bit of a number 
 * https://codeforwin.org/2016/01/c-program-to-get-value-of-nth-bit-of-number.html
 * Write a C program to input any number from user and check whether nth bit of the given number is set (1) or not (0).
 */
 
// Weishaupt1776

#include <stdio.h>
#include "get.h"

int bitlen(unsigned d);

int main(void)
{
	int num, numBitlen, n;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	numBitlen = bitlen(num);
	printf("Enter a number for the n'th bit: ");
	scanf("%i", &n);
	
	if((n+1) > numBitlen)
	{
		printf("Error: invalid (n'th) bit\n");
		return 0;
	}
	else
	{
		int bitmask = ~(~0 << 1);
		bitmask <<= n;
		bitmask &= num;
		
		if(bitmask > 0)
			printf("n'th bit of %i was set (1)\n", num);
		else
			printf("n'th bit of %i was not set (0)\n", num);
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

