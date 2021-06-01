/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. */


#include <stdio.h>
#include "get.h"

int rightrot(int num, int bitShift);
int bitlen(unsigned d) ;

int main(void)
{
	int x = 745, shift = 3;
	rightrot(x, shift);
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


int rightrot(int num, int bitShift)
{
	int totalBits, lsb;
	totalBits = bitlen(num);
	lsb = 1;

	binaryCast(num); // prints the previous binary representation
	
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
	return num;
}

