/* C program to rotate bits of a number 
 * https://codeforwin.org/2017/12/c-program-rotate-number-bits.html
 * Write a C program to input a number and rotate bits of number using bitwise shift operators. How to rotate bits of a given number using bitwise operator in C programming.
 */
 
// left rotation. more research needs to be done on how the person solved this problem

#include <stdio.h>
#include "get.h"

int bitlen(unsigned d);

int main(void)
{
	int num, totalBits, bitShift, msb;
	
	printf("Enter any number: ");
	scanf("%i", &num);
	binaryCast(num);
	printf("Number of left rotations: ");
	scanf("%i", &bitShift); 
	totalBits = bitlen(num);
	
	for(int i = 0; i < bitShift; i++)
	{
		msb = 1; // sets the msb to 1 to begin testing
		msb <<= totalBits-1; // shift the testing bit to msb location
		msb &= num; // tests to see if bit was set
		
		// if bit was set
		if(msb != 0)
		{
			msb = 1; // sets the msb to 1 to begin testing
			msb <<= totalBits-1; // shift the testing bit to msb location
			num ^= msb; // turns off msb in num
			num <<= 1;
			msb = 1;
			num = msb | num;
		}
		
		// if bit was not set
		else if(msb == 0)
		{
			num <<= 1;
			msb = ~0;
			num &= msb;
		}
		
	}
	
	printf("New number: %i\n", num);
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
