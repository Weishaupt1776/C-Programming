/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a function
 * expand(s1,s2) that expands shorthand notation a-z in the string
 * s1 into the equivalent complete list abc...xyz in s2. Allow for
 * letters of either case and digits, and be prepared to handle cases
 * like a-b-c and -a-z. Arrange that a leading or - is taken literally.
 */


#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

void expand(char s1[], char s2[]);
void getinput(char t[], int limit);

int main(void)
{	
	char s1[MAXLINE]; // first array to hold all input
	char s2[MAXLINE]; // second array to expand all shorthand notation from s1
	
	getinput(s1, MAXLINE-1); // get and store input in string s1
	expand(s1,s2); // expands shorthand notation in s1 to s2
	printf("\n%s", s2);

	return 0;
}

void getinput(char t[], int limit)
{
	int c, i;
	
	for(i = 0; i<limit-1 && (c = getchar()) != EOF; i++)
	{
		t[i] = c;
	}
	t[i] = '\0';
}

/* copies string s1 into s2 expaning all shorthand notation */
void expand(char s1[], char s2[])
{
	int indexS1 = 0;
	int indexS2 = 0;
	
	while(s1[indexS1] != '\0')
	{
		/* if s1[indexS1] is an alphabetical character */
		if(isalpha(s1[indexS1]))
		{
			/* copy character in s1 to s2 then increment both indexes */
			s2[indexS2++] = s1[indexS1++];
			
			/* if the next character in s1 is a dash indicating shorthand */
			if(s1[indexS1] == '-')
			{
				/* copy character in s1 to s2 then increment both indexes */
				s2[indexS2++] = s1[indexS1++];
				if(isalpha(s1[indexS1]))
				{
					if(s1[indexS1-2] < s1[indexS1])
					{
						if(islower(s1[indexS1]))
						{
							for(int i = s1[indexS1-2]+1; i <= s1[indexS1]; i++)
							{
								s2[indexS2++] = (char)i;
								s2[indexS2++] = '-';
							}
							indexS1++;
						}
						else if(isupper(s1[indexS1]))
						{
							for(int i = s1[indexS1-2]+1; i <= s1[indexS1]; i++)
							{
								s2[indexS2++] = (char)i;
								s2[indexS2++] = '-';
							}
						}
							indexS1++;
					}
					else if(s1[indexS1-2] > s1[indexS1])
					{
						if(islower(s1[indexS1]))
						{
							for(int i = s1[indexS1-2]-1; i >= s1[indexS1]; i--)
							{
								s2[indexS2++] = (char)i;
								s2[indexS2++] = '-';
							}
							indexS1++;
						}
						else if(isupper(s1[indexS1]))
						{
							for(int i = s1[indexS1-2]-1; i >= s1[indexS1]; i--)
							{
								s2[indexS2++] = (char)i;
								s2[indexS2++] = '-';
							}
						}
							indexS1++;
					}
					else
					{
						s2[indexS2++] = s1[indexS1++];
					}
					
				}
				else
				{
					s2[indexS2++] = s1[indexS1++];
				}
			}
			else
			{
				s2[indexS2++] = s1[indexS1++];
			}
		}
		else if(isdigit(s1[indexS1]))
		{
			s2[indexS2++] = s1[indexS1++];
			if(s1[indexS1] == '-')
			{
				s2[indexS2++] = s1[indexS1++];
				if(isdigit(s1[indexS1]))
				{
					if(s1[indexS1-2] > s1[indexS1])
					{
						for(int i = s1[indexS1-2]-1; i >= s1[indexS1]; i--)
						{
							s2[indexS2++] = (char)i;
							s2[indexS2++] = '-';
						}
						indexS1++;
					}
					else if(s1[indexS1-2] < s1[indexS1])
					{
						for(int i = s1[indexS1-2], j = 1; i < s1[indexS1]; i++, j++)
						{
							s2[indexS2++] = (char)s1[indexS1-2]+j;
							s2[indexS2++] = '-';
						
						}
						indexS1++;
					}
					else
					{
						s2[indexS2++] = s1[indexS1++];
					}
				}
				else
				{
					s2[indexS2++] = s1[indexS1++];
				}
			}
			else
			{
				s2[indexS2++] = s1[indexS1++];
			}
			
		}
		else
		{
			s2[indexS2++] = s1[indexS1++];
		}
	}
	s2[indexS2] = '\0';
}
