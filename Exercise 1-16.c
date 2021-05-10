/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Revise the main routine of
 * the longest-line program so it will correctly print the length of
 * arbitrarily long input lines, and as much as possible of the text.
 */
 
 /* I am assuming that this problem is asking to print the length
  * of random input lines from the user, and then all the text
  * including the longest line until the MAXLINE symbolic constant
  * has been reached.
  */
 
#include <stdio.h>
#define MAXLENGTH 1000
#define RECORD 100

int getinput(char s[], int lim);
void copy(char to[], char from[]);
 
int main(void)
{
	int len;
	int index;
	int record_index;
	int count_index;
	int max;
	char line[MAXLENGTH];
	char longest[MAXLENGTH];
	char stored_text[MAXLENGTH];
	int len_history[RECORD];
	
	for(index = 0; index < RECORD; index++)
	{
		len_history[index] = 0;
	}
	
	max = 0;
	index = 0;
	record_index = 0;
	count_index = 0;
	while((len_history[index] = len = getinput(line, MAXLENGTH)) > 0)
	{	
		index++;
		while(count_index < len)
		{
			stored_text[record_index] = line[count_index];
			count_index++;
			record_index++;
		}
		count_index = 0;
		
		if(len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	stored_text[record_index] = '\0';
	index = 0;
	printf("\nLength of input lines:\n");
	while(len_history[index] != 0)
	{
		printf("Input line #%i: %i\n", index + 1, len_history[index]);
		index++;
	}
	
	printf("\nText input:\n");
	if(max > 0)
	{
		printf("%s", stored_text);
		printf("\nLongest Line:\n%s", longest);
	}
	
	return 0;
}

int getinput(char s[], int lim)
{
	int c, i;
	
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		s[i] = c;
	}
	if(c == '\n')
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[])
{
	int i;
	
	i = 0;
	while((to[i] = from [i]) != '\0')
		i++;
}
