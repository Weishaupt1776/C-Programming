/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to remove
 * trailing blanks and tabs from each line of input, and to delete
 * entirely blank lines.
 */
 
 /* Program successfully deletea entirely blank lines, removes leading 
  * blanks, and also removes trailing blanks. 
  */
 
#include <stdio.h>
#define MAXLENGTH 1000
#define FALSE 0
#define TRUE 1

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
		while(count_index < len)
		{
			stored_text[position_index] = line[count_index];
			position_index++;
			count_index++;
		}
		count_index = 0;
	}
	
	stored_text[position_index] = '\0';
	printf("\nText input:\n");
	printf("%s", stored_text);
	
	return 0;
}

int getinput(char s[], int lim)
{
	int initial_keystroke = FALSE;
	int wspace = FALSE;
	int i, c;
	
	i = 0;
	while(i < lim-1 && (c = getchar()) != EOF)
	{
		if(initial_keystroke == FALSE) // removes any leading blanks
		{
			if(c == ' ' || c == '\t' || c == '\n')
				;
			else if(c != ' ' && c != '\t' && c != '\n')
			{
				s[i] = c;
				initial_keystroke = TRUE;
				i++;
			}
		}
		else if(initial_keystroke == TRUE)
		{
			if(c != ' ' && c != '\t' && c != '\n')
			{
				s[i] = c;
				i++;
				if(wspace == TRUE) // if there was a space before
				{
					wspace = FALSE; // you are now in a word
				}
			}
			else if(c == ' ' || c == '\t' || c == '\n')
			{
				if(wspace == FALSE)
				{
					s[i] = c;
					i++;
					wspace = TRUE;;
				}
				else if(wspace == TRUE)
					; // do nothing and remove trailing blanks
			}
		}
	}
	
	if(c == '\n')
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}
