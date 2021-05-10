/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to copy
 * its input to its output, replacing each tab by \t, each backspace
 * by \b, and each backslash by \\. This makes tabs and backspaces 
 * visible in an unambiguous way.
 */

#include <stdio.h>

int main(void)
{
	int c;
	
	while((c = getchar()) != EOF)
	{
		if(c == '\t')
			printf("\\t");
		else if(c == '\b')
			printf("\\b");
		else if(c == '\\')
			printf("\\\\");
		else
			putchar(c);
	}
	return 0;
}
