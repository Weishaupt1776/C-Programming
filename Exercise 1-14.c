/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to print
 * a histogram of the frequencies of different characters in its input.
 */
 
#include <stdio.h>
#define ALPHABET 26

int main(void)
{
	int c; // holds character from input
	int character_count[ALPHABET]; // creates array to store different occurrences of each character from stdin
	
	for(int i = 0; i < ALPHABET; i++)
	{
		character_count[i] = 0; // set all index values in array to 0
	}
	
	while((c = getchar()) != EOF)
	{
		if(c >= 'a' && c <= 'z') // if c is an lowercase alphabetical character
		{
			int x = c - 97;
			++character_count[x];
		}
		else if(c >= 'A' && c <= 'Z') // if c is an uppercase alphabetical character
		{
			int x = c - 65;
			++character_count[x];
		}
		else
			;
	}
	
	printf("Histogram of frequencies of different alphabetical characters:\n");
	for(int i = 0; i < ALPHABET; i++)
	{
		int j = character_count[i];
		int index = 0;
		printf("%c: ", (char)i+65); // prints alphabet table to make histogram clearer
		
		if(j == 0) // if there is no count in current array index
		{
			putchar('\n'); // print newline
		}
		
		else if(j > 0) // if data was encountered
		{
			while(index < j)
			{
				putchar('*'); // print asterik for each character input
				index++; // increment index by 1
			}
			putchar('\n'); // print newline
			index = 0; // reset index counter
		}
	}
	return 0;
}
