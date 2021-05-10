/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to print
 * all input lines that are longer than 80 characters.
 */

#include <stdio.h>
#define MAXLENGTH 1000

int getinput(char s[], int lim);
void copy(char to[], char from[]);
 
int main(void)
{
	int len;
	int position_index;
	int count_index;
	char line[MAXLENGTH];
	char stored_text[MAXLENGTH];
	
	position_index = 0;
	count_index = 0;
	while((len = getinput(line, MAXLENGTH)) > 0)
	{	
		if(len > 80)
		{	
			while(count_index < len)
			{
				stored_text[position_index] = line[count_index];
				count_index++;
				position_index++;
			}
			count_index = 0;
		}
	}
	stored_text[position_index] = '\0';
	
	printf("\nText input longer than 80 characters:\n");
	printf("%s", stored_text);
	
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

