/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a function
 * any(s1, s2), which returns the first location in the string s1
 * where any character from the string s2 occurs, or -1 of s1 contains
 * no characters from s2.
 */


#include <stdio.h>
#include <string.h>
#include "get.h"

int any(char s1[], char s2[]);

int main(void)
{
	int position;
	char* str1;
	char* str2;
		
	printf("Enter the first string: \n");
	str1 = get_string();
	printf("Enter the second string: \n");
	str2 = get_string();
	
	position = any(str1, str2);
	if(position == -1)
	{
		printf("No characters in second string occur in first string\n");
		printf("position: %i\n", position);
	}
	else
	{
		printf("First index where second string character appears in first string: %i\n", position);
	}
	
	return 0;
}

int any(char s1[], char s2[])
{
	short s1Size = strlen(s1);
	short s2Size = strlen(s2);
	
	for(int mainLoopIndex = 0; mainLoopIndex < s1Size; mainLoopIndex++)
	{
		for(int subLoopIndex = 0; subLoopIndex < s2Size; /* subLoopIndex controlled inside loop body */)
		{
			if(s1[mainLoopIndex] != s2[subLoopIndex])
			{
				subLoopIndex++;
			}
			else if(s1[mainLoopIndex] == s2[subLoopIndex])
			{
				return mainLoopIndex;
			}
		}
	}
	
	return -1;
}

