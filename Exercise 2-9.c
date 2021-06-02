/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. In a two's complement 
 * number system, x &= (x-1) deletes the rightmost 1-bit in x. 
 * Explain why. Use this observation to write a faster version of 
 * bitcount 
 */
 
 /* In a two's complement  number system, x &= (x-1) deletes the rightmost 1-bit in x. 
 * Q: Explain why. 
 * A: In order to understand why x &= (x-1) deletes the rightmost 1-bit of x, we must 
 * first understand the effect of (x-1). Imagine we have an unsigned number, e.g. 225,
 * this number will represent our 'x' value. We must first convert this to 
 * its equivalent binary representation, e.g. 225 in binary is 11100001.
 * After we convert 225 to binary we then subtract 1 from it as illustrated in (x-1) 
 * and the result will invariably invert the rightmost 1-bit to 0, 11100000.
 * Finally, we take the two distinct binary numbers, 11100001 and 11100000, and then
 * perform a bitwise & operation. The result will remove the rightmost 1-bit because
 * for a bitwise & operation to output '1' both operands need to have a 1-bit in 
 * their the corresponsing bit. 
 * Example: 225 &= 224
 * 11100001
 * 11100000
 * The result will be 11100000, because the lsb on both operands are not both 1.
 * This result will continuously cascade until there is no more 1-bits.
 * Example: 224 &= 223
 * 11100000
 * 11011111
 * The result will be 11000000, which is removing the previous 1-bit from 224.
 * This will occur until there are no more one bits. This even applies to negative values.
 */

#include <stdio.h>
#include "get.h"

int bitcount(int x);

int main(void)
{
	int x = 225;
	binaryCast(x);
	printf("Total 1-bits in %i: %i\n", x, bitcount(x));
	return 0;
}

int bitcount(int x)
{
	int bits;
	
	for(bits = 0; x != 0; x &= x-1)
		bits++;
	
	return bits;
}
