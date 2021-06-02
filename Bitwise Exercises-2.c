/* C program to check Most Significant Bit (MSB) of a number is set or not 
 * https://codeforwin.org/2016/01/c-program-to-check-most-significant-bit-of-number-is-set-or-not.html
 * Write a C program to input any number from user and check whether Most Significant Bit (MSB) of given number is set (1) or not (0).
 */

// Weishaupt1776

#include <stdio.h>

void decToBinary(int n);
int bitlen(unsigned d) ;

int main()
{
    int num, num2, msb;
    int bits = sizeof(num) * 8;

    /* Input number from user */
    printf("Enter any number: ");
    scanf("%d", &num);
    num2 = num;

	num2 >>= (bits-1);
	
    /* Move first bit of 1 to highest order */
    msb = ~(~0 << 1);

    /* Perform bitwise AND with msb and num */
    if(num2 & msb)
        printf("MSB of %d is set (1).", num);
    else
        printf("MSB of %d is unset (0).", num);

    return 0;
}
