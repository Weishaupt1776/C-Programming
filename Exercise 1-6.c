/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Verify that the expression
 * getchar() != EOF is 0 or 1.
 */

#include <stdio.h>

int main(void)
{
	int c = getchar() != EOF; // This is apparently a valid expression
	printf("%i\n", c);
	return 0;
}
