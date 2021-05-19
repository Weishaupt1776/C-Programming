/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program detab
 * that replaces tabs in the input with the proper number of blanks to
 * space to the next tab stop. Assume a fixed set of tab stops, say
 * every n columns. Should n be a variable or a symbolic parameter?
 */
 
 /* TABSTOP should be a symbolic constant as the location of the tabstops
  * or columns is fixed and does not change. n should be a variable 
  * to keep track of the location relative to the next tabstop.
  * */
 
 /* Weishaupt1776
  * David Serrano*/

#include <stdio.h>
#define TABSTOP 8
#define MAXLENGTH 2048 // 2 Kilobytes

int getinput(char s[], int lim);

int main(void)
{
	char input[MAXLENGTH]; // character array which will contain input
	int EOF_check; // variable that holds value of input to test EOF

	while((EOF_check = getinput(input, MAXLENGTH)) > 0)
	{
		printf("%s\n", input); // print out string in entirety
	}
	
	
	return 0;
}

/* Modified version of geninput */
int getinput(char s[], int lim)
{
	int c; // holds character input
	int i; // loop control
	int n = 8; // amount of places until next tabstop
	
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; /* all increments done in loop body */)
	{
		if(c != '\t')
		{
			s[i] = c; // store character in s[]
			i++; // increment i variable
			n--; // decrement n variable
		}
		else if(c == '\t')
		{
			while(n > 0)
			{
				s[i] = '-';
				n--;
				i++;
			}
			n = 8; // reset counter variable
		}
		if(n == 0) // reset counter variable
		{
			n = 8;
		}
	}
	if(c == '\n')
	{
		s[i] = '\0';
	}
	return i;
}
