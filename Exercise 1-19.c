/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a function reverse(s)
 * that reverses the character string s. Use it to write a program
 * that reverses its input one line at a time.
 */
 
 /* Weishaupt1776
    David Serrano
  */
 
#include <stdio.h>
#define MAXLENGTH 1000

int reverse(char text[], int index);
 
int main(void)
{	
	int EOF_test; // control mechanism to test for EOF encounter
	int index = 0; // keeps track of position inside character array
	char text[MAXLENGTH]; // character array
	
	while((EOF_test = reverse(text, index)) > 0)
	{
		index = EOF_test; // update index to parse through array
	}
	
	printf("%s", text); // print string
	return 0;
}

int reverse(char text[], int index)
{
	char reverse_text[MAXLENGTH]; // array which holds the reversed text
	int limit = MAXLENGTH-1; // sets limit for maximum input
	int parsing_marker; // keeps track of index in reverse_text array
	int back_marker; // help parse text array backwards for copying
	int character; // holds current character from stdin
	
	
	/* getting input from stdin */
	for( /* No initialization here */ ; index <= limit && (character = getchar()) != EOF && character != '\n'; index++)
	{
		text[index] = character;
	}
	if(character == '\n')
	{
		text[index] = character;
		index++;
	}
	text[index] = '\0';
	parsing_marker = index - 1; 
	back_marker = index - 1; 
	 
	/* actually reversing input one line at a time */
	if(index == 0) // if there was never any input
	{
		; // just do nothing
	}
	else if(text[parsing_marker] == '\n')
	{
		parsing_marker = parsing_marker - 1; // marker is inside text
		if(parsing_marker == 0) // if you are at the first character in array
		{
			reverse_text[parsing_marker] = text[parsing_marker];
			parsing_marker++;
			reverse_text[parsing_marker] = '\n';
			parsing_marker++; 
			reverse_text[parsing_marker] = '\0';
		}
		else if(parsing_marker != 0)
		{
			while(text[parsing_marker] != '\n' && parsing_marker != 0)
			{
				parsing_marker--; // should manupulate the parsing_index to be at the last newline character
			}
			if(text[parsing_marker] == '\n')
			{
				parsing_marker++;
			}
			while(parsing_marker != index)
			{
				reverse_text[parsing_marker] = text[back_marker];
				parsing_marker++;
				back_marker--;
			}
		}
	}
	 
	 
	/* returning the necessary value to ensure proper
	 * function execution */	 
	if(character == EOF) // if EOF was encountered
	{
		int count = 0;
		while(count < index)
		{
			text[count] = reverse_text[count];
			count++;
		}
		text[count] = '\0';
		return EOF;
	}
	else if(index == limit) // if limit was reached
	{
		int count = 0;
		while(count < index)
		{
			text[count] = reverse_text[count];
			count++;
		}
		text[count] = '\0';
		return EOF;
	}
	else // if no EOF or limit was reached
		return index;
}
