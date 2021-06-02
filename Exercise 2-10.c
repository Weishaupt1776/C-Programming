/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Rewrite the function lower,
 * which converts upper case letters to lower case, with a conditional 
 * expression instead of if-else.
 */


#include <stdio.h>
#include <string.h>
#include "get.h"

void lower(char* string);

int main(void)
{
	char* string;
	printf("Enter string: ");
	string = get_string();
	printf("New string: ");
	lower(string);
	return 0;
}

void lower(char* string)
{
	int stringlength = strlen(string);
	
	for(int i = 0; i < stringlength; i++)
	{
		(string[i] >= 'A' && string [i] <= 'Z') ? string[i] += 32 : string[i];
	}
	
	printf("%s\n", string);
}

