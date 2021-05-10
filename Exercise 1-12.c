/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program that
 * prints its input one word per line.
 */
 
#include <stdio.h>

#define OUT 0
#define IN 1

int main(void)
{
	int c; // variable which holds user input
	int state = OUT; // initially, not in a word
	int marker = IN; // initially, no newline character has been printed
	
	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\n' || c == '\t')
		{
			if(marker == OUT)
			{
				marker = IN;
				putchar('\n');
			}
		}
		else if(c != ' ' || c != '\n' || c != '\t')
		{
			putchar(c);
			state = IN;
			marker = OUT;
		}
	}
	return 0;
}
