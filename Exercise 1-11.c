/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. How would you test the
 * word count program? What kinds of input are most likely to uncover
 * bugs if there are any?
 */
 
#include <stdio.h>
 
 #define IN 1
 #define OUT 0
 
 /* counts lines, words, and characters in input */
 
int main(void)
{
	int c, nl, nw, nc, state;
	
	state = OUT;
	nl = 0;
	nw = 0;
	nc = 0;
	
	while((c = getchar()) != EOF)
	{
		++nc;
		if(c == '\n')
		{
			++nl;
		}
		else if(c == ' ' || c == '\n' || c == '\t')
		{
			state = OUT;
		}
		else if(state == OUT)
		{
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
	return 0;
}
