/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write an alternate
 * version of squeeze(s1, s2) that deletes each character in s1
 * that matches any character in the string s2.
 */

#include <stdio.h>
#include <string.h>
#include "get.h"

void squeeze(char s1[], char s2[]);
enum copyState { SAME, NOTSAME };

int main(void)
{
	printf("Enter the first string: \n");
	char* str1 = get_string();
	printf("Enter the second string: \n");
	char* str2 = get_string();
	squeeze(str1, str2);
	printf("Resulting string is: %s\n", str1);
	return 0;
}

void squeeze(char s1[], char s2[])
{
	short s1Size = strlen(s1);
	short s2Size = strlen(s2);
	char s3[s1Size];
	int squeezeTest = NOTSAME;
	int mainIndex = 0;
	
	for(int mainLoopIndex = 0; mainLoopIndex < s1Size; mainLoopIndex++)
	{
		for(int subLoopIndex = 0; subLoopIndex < s2Size && squeezeTest != SAME; /* loop increment within body */)
		{
			if(s1[mainLoopIndex] != s2[subLoopIndex])
			{
				squeezeTest = NOTSAME;
				subLoopIndex++; 
			}
			else if(s1[mainLoopIndex] == s2[subLoopIndex])
			{
				squeezeTest = SAME;
			}
		}
		if(squeezeTest == NOTSAME)
		{
			s3[mainIndex++] = s1[mainLoopIndex];
		}
		else if(squeezeTest == SAME)
		{
			squeezeTest = NOTSAME;
		}
	}
	s3[mainIndex] = '\0';
	mainIndex = 0;
	while(s1[mainIndex] != '\0')
	{
		s1[mainIndex] = s3[mainIndex];
		mainIndex++;
	}
}
