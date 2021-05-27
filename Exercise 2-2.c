/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a loop equivalent
 * to the for loop above without using && or ||.
 */
 
 /* This is a reference to Chapter 1:
  * for(i=0; i<lim-1 && (c = getchar()) != '\n' && c!= EOF; ++i) 
  *     s[i] = c;
  */

#include <stdio.h>
#define MAXLINE 1000

int getinput(char s[], int lim);

int main(void)
{
	char line[MAXLINE];
	int limit = MAXLINE-1;
	int length = 0;
	while((length = getinput(line, limit)) > 0)
	{
		; // do nothing
	}
	return 0;
}

/* getline: read a line into s, return length */
int getinput(char s[], int lim)
{
	int c, i;
	
	for(i = 0; i < lim-1; ++i)
	{
		if((c = getchar()) == EOF)
		{
			s[i] = '\0';
			return i;
		}
		else if(c != '\n')
		{
			if(c != EOF)
			{
				s[i] = c;
			}
		}
		else if(c == '\n')
		{
			s[i] = c;
			++i;
			s[i] = '\0';
			return i;
		}
	}
	return i;
}
