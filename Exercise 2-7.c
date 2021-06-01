/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a function invert(x,p,n)
 * that returns x with the n bits that begin at position p inverted
 * (i.e., 1 changed into 0 and vice versa), leaving the other bits
 * unchanged.
 */

#include <stdio.h>
#include "get.h"

unsigned getbits(unsigned x, unsigned p, unsigned n);
unsigned invert(unsigned x, unsigned p, unsigned n);
int bitlen(unsigned d);

int main(void)
{
	int x = 999 , p = 5, n = 3;
	decToBinary(x);
	x = invert(x,p,n);
	decToBinary(x);
	return 0;
}

/* getbits: get n bits from position p
 */
unsigned getbits(unsigned x, unsigned p, unsigned n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
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


unsigned invert(unsigned x, unsigned p, unsigned n)
{
	int centralBits = getbits(x, p, n); // get bits
	int bitfieldLen = bitlen(x);
	int leftBits = getbits(x, bitfieldLen-1, bitfieldLen-1-p);
	int totalLeftBits = bitfieldLen-1-p;
	int rightBits = getbits(x, p-n, bitfieldLen - (totalLeftBits+n));
	
	/* reverses the desired bits */
	for(int i = 0; i < n; i++)
	{
		int bitmask = 1;
		bitmask <<= i;
		centralBits ^= bitmask;
	}
	
	centralBits <<= p+1-n; // shifts bits to desired location
	leftBits <<= bitfieldLen-totalLeftBits; // shifts bits to desired location
	leftBits |= centralBits; // combines bitfields
	leftBits |= rightBits; // combines bitfields
	
	x = leftBits;
	
	return x;
}
