/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a function 
 * setbits(x,p,n,y) that reurns x with the n bits that begin at
 * position p set to the rightmost n bits of y, leaving the other
 * bits unchanged.
 */

#include <stdio.h>
#include "get.h"

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);
unsigned getbits(unsigned x, int p, int n);
void decToBinary(int n);
int bitlen(unsigned d);

int main(void)
{
	unsigned x = 745;
	unsigned y = 360;
	unsigned p = 6;
	unsigned n = 4;
	x = setbits(x,p,n,y);
	decToBinary(x);
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

/* getbits: get n bits from position p
 */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* Some properties of this function are borrowed from the user fool2fish on github
 * https://github.com/fool2fish/the-c-programming-language-exercise-answers/blob/master/ch02/2-6.c
 */
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
	unsigned centralBitfield = getbits(y, n-1, n); // stores desired bits from 'y' in variable 'bitfield'
	unsigned lenx = bitlen(x); // gets total amount of bits in x
	unsigned leny = bitlen(y); // gets total amount of bits in y
	unsigned totalLeftBits = lenx - (p+1); // total bits to left of 'n' bitfield
	unsigned totalRightBits = p+1-n; // total bits to right of 'n' bitfield
	unsigned leftBitfield = ~0 << (lenx-totalLeftBits); // creates a bitmask of '111...' over the leftBitfield of 'x'
	unsigned rightBitfield = ~(~0 << totalRightBits); // creates a bitmask of '111...' over the rightBitfield of 'x'
	

	if (lenx-1 < p || n > p+1 || lenx < n || leny < n)
	{
		printf("Error: illegal p<%u> or n<%u>.\n", p, n);
		return 0;
	}
	else 
	{
		centralBitfield = (centralBitfield << (p+1-n)); // contains the required central bitfield
		leftBitfield &= x; // contains the required left bitfield
		rightBitfield &= x; // contains the required right bitfield
		x = leftBitfield | centralBitfield;
		x = x | rightBitfield;
		return x;
	}
}

/* This function is borrowed from geekforgeeks.org
 * https://www.geeksforgeeks.org/program-decimal-binary-conversion
 */
void decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];
 
    // counter for binary array
    int i = 0;
    while (n > 0) 
    {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 
    // printing binary array in reverse order
    for(int j = i - 1; j >= 0; j--)
    {
        printf("%i", binaryNum[j]);
    }
    putchar('\n');
}
