/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Adapt the ideas of printd
 * to write a recursive version of itoa; that is, convert an integer 
 * into a string by calling a recursive routine.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHARS 64

void itoa(int n, char s[]);

int main(void)
{
	char s[MAXCHARS];
	int n = -300;
	itoa(n,s);
	printf("%s\n", s);
	return 0;
}

/* printd: print n in decimal */
void itoa(int n, char s[])
{
	/* index for assigning proper char */
	static int index = 0;
	
	if (n < 0)
	{
		s[index++] = '-';
		n = -n;
	}
	if (n / 10)
	{
		itoa(n / 10, s);
	}
	
	s[index++] = (n % 10 + '0');
	s[index] = '\0';
}
