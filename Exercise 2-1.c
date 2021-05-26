/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to
 * determine the ranges of char, short, int, and long variables, 
 * both signed and unsigned, by printing appropriate values from
 * standard headers and by direct computation. Harder if you compute
 * them; determine the ranges of the various floating-point types.
 */
 
 // Weishaupt1776

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main(void)
{
	
	printf("Limits.h:\n");
	printf("The amount of bits in a char variable: %i\n", CHAR_BIT);
	printf("The maximum value of a signed char: %i\n", SCHAR_MAX);
	printf("The minimum value of a signed char: %i\n", CHAR_MIN);
	printf("The maximum value of an unsigned char: %i\n", UCHAR_MAX);
	printf("The minumum value of an unsigned char: %i\n", 0);
	printf("The maximum value of a signed int variable: %i\n", INT_MAX);
	printf("The minimum value of a signed int variable: %i\n", INT_MIN);
	printf("The maximum value of an unsigned int variable: %u\n", UINT_MAX);
	printf("The minimum value of an unsigend int variable: %i\n", 0);
	printf("The maximum value of a short variable: %i\n", SHRT_MAX);
	printf("The minimum value of a short variable: %i\n", SHRT_MIN);
	printf("The maximum value of an unsigned short variable: %i\n", USHRT_MAX);
	printf("The minimum value of an unsigned short variable: %i\n", 0);
	printf("The maximum value of a long variable: %li\n", LONG_MAX);
	printf("The minimum value of a long variable: %li\n", LONG_MIN);
	printf("The maximum value of an unsigned long variable: %lu\n", ULONG_MAX);
	printf("The minimum value of an unsigned long variable: %i\n", 0);
	
	
	printf("\nDirect Computation:\n");
	printf("Maximum value of signed char: %.0f\n", ((pow((double)2, (double)sizeof(char) * 8)) / 2) - 1);
	printf("Minimum value of signed char: -%.0f\n", (pow((double)2, (double)sizeof(char) * 8)) / 2);
	printf("Maximum value of unsigned char: %.0f\n", pow((double)2, (double)sizeof(char) * 8) - 1);
	printf("Minimum value of unsigned char: %.0f\n", (double)0);
	printf("Maximum value of signed int: %.0f\n", ((pow((double)2, (double)sizeof(signed int) * 8)) / 2) - 1);
	printf("Minimum value of signed int: -%.0f\n", (pow((double)2, (double)sizeof(signed int) * 8)) / 2);
	printf("Maximum value of unsigned int: %.0f\n", pow((double)2, (double)sizeof(unsigned int) * 8) - 1);
	printf("Minimum value of a unsigned int: %.0f\n", (double)0);
	printf("Maximum value of a signed short: %.0f\n", ((pow((double)2, (double)sizeof(signed short) * 8)) / 2) - 1);
	printf("Minimum value of a signed short: -%.0f\n", (pow((double)2, (double)sizeof(signed short) * 8)) / 2);
	printf("Maximum value of unsigned short: %.0f\n", pow((double)2, (double)sizeof(unsigned short) * 8) - 1);
	printf("Minimum value of unsigned short: %.0f\n", (double)0);
	printf("Maximum value of signed long: %li\n", (long)pow(2, 64));
	printf("Minimum value of signed long: -%.0f\n", (pow((double)2, (double)sizeof(signed long long) * 8)) / 2);
	printf("Maximum value of unsigned long: %lu\n", (long)pow(2, 64) * 2 + 1);
	printf("Minimum value of unsigned long: %.0f\n", (double)0);
	
	
	return 0;
}
