/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to
 * count blanks, tabs, and newlines.
 */
 
 #include <stdio.h>
 
int main(void)
{
	int nlines = 0, tabs= 0, blanks = 0;
	int c;
	
	while((c = getchar()) != EOF)
	{
		if(c == ' ')
			++blanks;
		else if(c == '\t')
			++tabs;
		else if(c == '\n')
			++nlines;
	}
	printf("Total blanks: %i\nTotal tabs: %i\nTotal newlines: %i\n", blanks, tabs, nlines);
	return 0;
}
