/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write the function
 * strrindex(s,t), which returns the position of the rightmost
 * occurence of t in s, or -1 if there is none.
 */


#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

void copystring(char to[], char from[]);
void reverse(char s[]);
int strrindex(char s[], char t[]);

char pattern[] = "booze";

int main(void)
{
	int index;
	char s[] = "There is no booze in this house!\n";
	index = strrindex(s, pattern);
	printf("%i\n", index);
	return 0;
}

/* copystring: copies a string to another array */
void copystring(char to[], char from[])
{
	int i;
	
	for(i = 0; (to[i] = from[i]) != '\0'; i++)
	{
		continue;
	}
	to[i] = '\0';
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;
	
	for(i = 0, j = strlen(s)-1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* strrindex: returns index of rightmost occurrence of 't' */
int strrindex(char s[], char t[])
{
	int mainindex, parseIndex, count, patternlength;
	char searchfor[MAXLINE];
	
	patternlength = strlen(t);
	copystring(searchfor, t);
	reverse(searchfor);
	
	for(mainindex  = strlen(s) - 1; mainindex >= 0; mainindex--)
	{
		for(parseIndex = 0, count = 0; searchfor[parseIndex] != '\0' && s[mainindex-count] == searchfor[parseIndex]; parseIndex++, count++)
		{
			;
		}
		
		if(count == patternlength)
		{
			return mainindex - count + 1;
		}
	}
	
	return -1;
}
