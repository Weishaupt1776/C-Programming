/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a recursive version
 * of the function reverse(s), which reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

#define MAXCHARS 64

void reverse(char s[]);

int main(void)
{
	char s[] = "DOG";
	reverse(s);
	printf("%s\n", s);
	return 0;
}

/* reverse: reverses a string in place recursively */
void reverse(char s[])
{
	/* length of s[] */
	static int len = 0;
	static int lencpy = 0;
	static char reversed[MAXCHARS];
	
	while (s[len] != '\0')
	{
		len++;
		lencpy++;
	}
	
	if (lencpy > 0)
	{
		lencpy--;
		reverse(s);
	}
	
	if (lencpy < len)
	{
		reversed[lencpy] = s[len - 1 - lencpy];
		lencpy++;
	}
	
	if(lencpy == len)
	{
		strcpy(s, reversed);
	}
}
