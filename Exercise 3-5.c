/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write the function
 * itob(n,s,b) that converts the integer n into a base b character
 * representation in the string s. In particular, itob(n,s,16) 
 * formats n as a hexadecimal integer in s.
 */


#include <stdio.h>
#include <string.h>
#include <math.h>

void itob(int n, char s[], int b);
long long ipow(int base, int exp);

int main(void)
{
	int n = 144;
	int b = 3;
	char s[64];
	itob(n,s,b);
	printf("%s\n", s);
	return 0;
}

/* function to return power of an integer raised to an exponent */
long long ipow(int base, int exp)
{
    long long result = base;
    
    if(exp == 0)
    {
		result = 1;
		return result;
	}
	else if(exp == 1)
	{
		result = base;
		return result;
	}
	else
	{
		int count = 1;
		
		while(count != exp)
		{
			result = result * base;
			count++;
		}
		
		return result;
	}
	
}

void itob(int n, char s[], int b)
{	
	/* declaring and initializing variables */
	int baseValue, exp, result, digit, refValue, index;
	baseValue = exp = result = digit = index = 0;
	refValue = n;
	
	if(b > 9)
	{
		printf("Error: base must be 9 or less\n");
		s[index] = '\0';
		return;
	}
	
	/* get the highest baseValue of new base */
	while((baseValue = ipow(b, exp)) < n)
	{
		exp++;
	}
	exp -= 1;
	baseValue = ipow(b, exp);
	
	/* main work is done here */
	while(refValue > 0)
	{
		result = baseValue * digit;
		
		while((result < refValue) && (digit < b-1))
		{
			digit++;
			result = baseValue * digit;
		}
		
		if((digit == (b-1)) && (result < refValue))
		{
			result = baseValue * digit;
			refValue -= result;
			exp--;
			baseValue = ipow(b,exp);
			s[index++] = (char)'0' + digit;
			digit = 0;
		}
		else if(result == refValue)
		{
			refValue -= result;
			exp--;
			s[index++] = (char)'0' + digit;
			digit = 0;
		}
		else
		{
			digit--;
			result = baseValue * digit;
			refValue -= result;
			exp--;
			baseValue = ipow(b,exp);
			s[index++] = (char)'0' + digit;
			digit = 0;
		}
	}
	
	while(exp >= 0)
	{
		s[index++] = (char)'0';
		exp--;
	}
	
	s[index] = '\0';
}


