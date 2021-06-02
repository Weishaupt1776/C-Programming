/* C program to rotate bits of a number 
 * https://codeforwin.org/2017/12/c-program-rotate-number-bits.html
 * Write a C program to input a number and rotate bits of number using bitwise shift operators. How to rotate bits of a given number using bitwise operator in C programming.
 */

// Right rotation

#include <stdio.h>
#include "get.h"

int bitlen(unsigned d);

int main(void)
{
	int num, totalBits, bitShift, lsb;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	binaryCast(num);
	printf("Number of right rotations: ");
	scanf("%i", &bitShift);
	totalBits = bitlen(num);
	
	for(int i = 0; i < bitShift; i++)
	{
		lsb = 1; // initialize lsb
		lsb &= num; // test if the lsb of num is '1' or '0'
		
		if(lsb == 1)
		{
			lsb <<= totalBits-1;
			num >>= 1;
			num |= lsb;
		}
		else if(lsb == 0)
		{
			lsb = 1; // set lsb back to '1' temporarily
			lsb <<= totalBits-1;
			lsb = ~lsb;
			num >>= 1;
			num &= lsb;
		} 
	}
	
	printf("New value: %i\n", num);
	binaryCast(num);
	
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
