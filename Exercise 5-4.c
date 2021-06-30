/*  This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write the function 
 * strend(s,t) ], which returns 1 if the string t occurs at the end of 
 * the string s, and zero otherwise. */


#include <stdio.h>
#include <string.h>
#define MAXCHARS 100

int strend(char *t, char *f);

int main(void)
{
	char t[MAXCHARS] = "Hello!";
	char f[MAXCHARS] = "lo!";
	strend(t,f);
	return 0;
}

/* strend: checks if string 'e' is at end of 'str' */
int strend(char *str, char *e)
{
	/* gets length of 'e' so we can check right amount of chars */
	int length = strlen(e);
	
	/* moves pointer 'str' to end of itself */
	while (*str)
		str++;
	/* moves back pointer 'str' by length of 'e' */
	for (int i = 0; i < length; i++)
	{
		str--;
	}
	
	/* checks if 'e' occurs at end of 'str' */
	for (int i = 0; i < length; i++) 
	{
		if (*str != *e)
		{
			printf("No occurence of string at the end!\n");
			return 0; /* string 'e 'did not occur at end of 'str' */
		}
		else
		{
			str++;
			e++;
		}
	}
	printf("String occurred!\n");
	return 1; /* 'e' did occur at the end of 'str' */
}

