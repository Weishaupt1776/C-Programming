/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program to "fold"
 * long input lines into two or more shorter lines after the last
 * non-blank character that occurs before the n-th column of input.
 * Make sure your program does something intelligent with very long
 * lines, and if there are no blanks or tabs before a specified column.
 */
 
#include <stdio.h>

#define FOLD 33 // marks the 33rd column as the "fold" marker in input
#define MAXLINE 1024 // maximum amount of space is 1024 bytes

int getinput(char s[], int lim);

int main(void)
{
	int EOF_check; // checks if EOF value has occurred
	int position; // keeps track of the position in input
	char input[MAXLINE]; // holds standard input from the user
	char folded[MAXLINE]; // array holds input and folds lines over
	
	while((EOF_check = getinput(input, MAXLINE)) > 0)
	{
		position = EOF_check; // sets the total of input to 'position'
		if(position >= FOLD) // if value of 'position' is atleast 33
		{
			int marker = FOLD;
			while((input[marker] != ' ' && input[marker] != '\t') && marker != 0)
			{
				marker -= 1; // decrement marker by 1
			}
			if(marker == 0)
			{
				/* In this case, the input will be folded exactly at column 33 */
				int index = 0;
				while(index != position)
				{
					folded[marker] = input[index];
					marker++;
					index++;
					if(marker == FOLD)
					{
						folded[marker] = '\n';
						marker++;
						folded[marker] = input[index];
						index++;
						marker++;
					}
				}
				folded[marker] = '\0';
			}
			else
			{
				int index = 0; // set index of new array
				while(index != marker)
				{
					folded[index] = input[index];
					index++;
				}
				folded[index] = '\n';
				index++;
				
				while(index != position)
				{
					folded[index] = input[index];
					index++;
				}
				folded[index] = '\0';
			}
		}
		else if(position <= FOLD)
		{
			int marker = 0;
			while(marker != position)
			{
				folded[marker] = input[marker];
				marker++;
			}
			folded[marker] = '\0';
		}
		printf("%s\n\n", folded);
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
		s[i] = '\0';
	}
	return i;
}
