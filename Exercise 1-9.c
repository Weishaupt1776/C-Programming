/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to copy
 * its input to its output, replacing each string of one or more
 * blanks by a single blank.
 */
 
#include <stdio.h>
#include <ctype.h>
#define OUT 0
#define IN 1
 
int main(void)
{
	int c;
	int state = OUT;
	int wspace_count = 0;
	
	while((c = getchar()) != EOF)
	{
		if(!isspace(c))
		{
			putchar(c);
			state = IN;
			wspace_count = 0;
		}
		else if(isspace(c) && wspace_count == 0)
		{
			state = OUT;
			putchar(c);
			wspace_count++;
		}
		else if(isspace(c) && wspace_count != 0)
		{
			state = OUT;
		}
	}
	return 0;
}
