/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a version of itoa
 * that accepts three arguments instead of two. The third argument is
 * the minimum field width; the converted number must be padded
 * with blanks on the left if necessary to make it wide enough.
 */


#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[], int width);


int main(void)
{
	int n, width;
	n = 5000, width = 10;
	char s[32];
	itoa(n,s,width);
	printf("%s\n", s);
	return 0;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;
	
	for(i = 0, j = strlen(s)-1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int width)
{
	int i, sign, nlen;
	
	if((sign = n) < 0)
		n = -n;
	
	i = 0;
	
	do
	{
		s[i++] = n % 10 + '0';
	} while((n /= 10) > 0);
	
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	
	nlen = strlen(s);
	if(nlen < width)
	{
		while(nlen < width)
		{
			s[i++] = ' ';
			nlen++;
		}
		s[i] = '\0';
		reverse(s);
	}
	else
	{
		reverse(s);
	}
}

