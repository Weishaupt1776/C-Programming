/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Extend atof to handle
 * scientific notation of the form 123.45e-6 where a floating-point
 * number may be followed by the e or E and an optionally signed
 * exponent. 
 */


#include <stdio.h>
#include <ctype.h>

double powerOf(int x, int n);
double atof(char s[]);

int main(void)
{
	char s[] = "-3.15e-4";
	double x = atof(s);
	printf("%f\n", x);
	return 0;
}

/* function borrowed from stackoverflow.com
 * https://stackoverflow.com/questions/15265230/c-writing-a-function-for-an-exponent-without-using-pow */
double powerOf(int x, int n)
{
    int i; /* Variable used in loop counter */
    int number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return (double)number;
}

/* atof: returns the equivalent floating-point value of s[] */
double atof(char s[])
{
	double val, power, baseValue;
	int i, exp, sign, expsign;
	
	/* checks for any invalid characters in string */
	for(i = 0; s[i] != '\0'; i++)
	{	
		if(!isdigit(s[i]) && s[i] != '+' && s[i] != '-' && s[i] != '.' && s[i] != 'e' && s[i] != 'E')
		{
			printf("Error: invalid format for atof(s[]) conversion\n");
			return -1;
		}
	}
	
	/* skips any blanks */
	for(i = 0; isspace(s[i]); i++)
	{
		continue;
	}
	/* determines if value is positive or negative */
	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
	{
		i++;
	}
	
	/* parses through and evaluates initial digit(s) of number  */
	for(val = 0.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
	}
	
	/* skips decimal-point and evaluates complete number */
	if(s[i] == '.')
	{
		/* skips '.' */
		i++;
		
		/* evaluates complete number */
		if(isdigit(s[i]))
		{
			for(power = 1.0; isdigit(s[i]); i++)
			{
				val = 10.0 * val + (s[i] - '0');
				power *= 10.0;
			}
		
			/* stores exact value of floating-point number */
			val = sign * val / power;
			
			/* checks if this was end of string */
			if(s[i] == '\0')
			{
				return val;
			}
		}
		
		/* check if there was an occurrence of 'e' or 'E' */
		if(s[i] == 'e' || s[i] == 'E')
		{
			/* skips 'e' */
			i++;
			
			/* get exponent sign value */
			expsign = (s[i] == '-') ? -1 : 1;
			
			/* skips over exponent sign */
			if(s[i] == '-' || s[i] == '+')
			{
				i++;
			}
			
			/* get exponent value */
			for(exp = 0.0; isdigit(s[i]); i++)
			{
				exp = 10.0 * exp + (s[i] - '0');
			}
			
			/* get base value */
			baseValue = powerOf(10, exp);
			
			/* return final answer */
			if(expsign == -1)
			{
				return val / baseValue;
			}
			else if(expsign == 1)
			{
				return val * baseValue;
			}
		}
		
	}

	if(s[i] == 'E' || s[i] == 'e')
	{
		/* skips 'e' */
		i++;
			
		/* get exponent sign value */
		expsign = (s[i] == '-') ? -1 : 1;
		
		/* skips over exponent sign */
		if(s[i] == '-' || s[i] == '+')
		{
			i++;
		}
			
		/* get exponent value */
		for(exp = 0.0; isdigit(s[i]); i++)
		{
			exp = 10.0 * exp + (s[i] - '0');
		}
			
		/* get base value */
		baseValue = powerOf(10, exp);
		
		/* return final answer */
		if(expsign == -1)
		{
			return val / baseValue;	
		}
		else if(expsign == 1)
		{
			return val * baseValue;
		}
	}
	
	
	
	return val;
}
