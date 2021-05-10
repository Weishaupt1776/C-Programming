/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to print
 * a histogram of the length of words in its input. It is easy to
 * draw the histogram with the bars horizontal; a vertical histogram
 * is more challenging.
 */
 
#include <stdio.h>
#define OUT 0
#define IN 1
#define MAXWORDLENGTH 24

int main(void)
{
	int c; // holds the character from user input
	int state = OUT; // initially we are not in a word
	int word_length = 0; // keeps track of length of word from input
	int word_count[MAXWORDLENGTH]; // word length database
	
	for(int i = 0; i < MAXWORDLENGTH; i++)
	{
		word_count[i] = 0; // sets all index values to zero
	}
	
	/* This while loop contains the bulk of the program where all the
	 * input is categorized and stored in an array to keep track of
	 * the different length of words encountered from stdin */
	
	while((c = getchar()) != EOF) // gather input from user, check if input was EOF value
	{
		if(c != ' ' && c != '\n' && c != '\t') // if user input was not a "blank"
		{
			if(word_length < MAXWORDLENGTH-1)
			{
				state = IN; // inside a word
				word_length = word_length + 1; // increment word length count by 1
			}
			else if(word_length == MAXWORDLENGTH-1)
			{
				; // stop counting input size
			}
		}
		
		else if(c == ' ' || c == '\n' || c == '\t') // if input was a blank
		{
			if(word_length > 0)
			{
				state = OUT; // outside a word
				++word_count[word_length]; // increment arr index by 1
				word_length = 0; // reset word_length count
			}
			else
				; // do nothing
		}
	}
	
	printf("\nHistogram of length of words:\n");
	for(int i = 0; i < MAXWORDLENGTH; i++)
	{
		int index = 0; // keeps track of position inside array index
		int j = word_count[i]; // variable j holds value inside array index
		printf("%i: ", i);
		if(j == 0) // if there is no count inside a particular index
		{
			putchar('\n'); // just print a newline
		}
		else if(j > 0) // if there is a count inside a particular index
		{
			while(index < j)
			{
				putchar('*');
				index++;
			}
			putchar('\n');
			index = 0;
		}
	}
	return 0; // program executed successfully
}
