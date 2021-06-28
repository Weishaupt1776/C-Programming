/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write getfloat, the
 * floating-point analog of getint. What type does getfloat return
 * as its function value.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define BUFSIZE 100

/* global variables */
int buf[BUFSIZE];
int bufp = 0;

/* functions */
int getch(void);
void ungetch(int c);
double getfloat(double *pn);

int main(void)
{
	double x;
	x = getfloat(&x);
	printf("The value of \"x\" is: %f\n", x);
	return 0;
}

/* get a (possibly pushed back) character */
int getch(void) 
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) 
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
double getfloat(double *pn)
{
	/* sign determines if neg or pos, c holds last char from stdin */
	int c, sign, floatTally;
	double floatValue = 0.0;
	
	/* skip white space */
	while (isspace(c = getch())) 
	{
		continue;
	}
	/* determine if c was a valid character */
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
	{
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1; /* determine if number is positive or negative */
	if (c == '+' || c == '-') /* if a sign was encountered, get next non-wspace char */
	{
		while (isspace(c = getch())) /* skip anymore wspace */
		{
			ungetch(c);
		}
		if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c!= '.') /* check for invalid characters */
		{
			ungetch(c);
			return 0;
		}
		if (isdigit(c)) /* check if c was a digit */
		{
			for(*pn = 0; isdigit(c); c = getch()) /* get integral value */
			{
				*pn = 10 * *pn + (c - '0');
			}
		}
		if(c == '.') /* if a decimal point was encountered */
		{
			while (isspace(c = getch())) /* skip anymore wspace */
			{
				ungetch(c);
			}
			if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') /* check for invalid characters */
			{
				ungetch(c);
				return 0;
			}
			for (floatValue = 0.0, floatTally = 0.0; isdigit(c); c = getch(),  floatTally++) /* get digits after decimal-point */
			{
				floatValue = 10 * floatValue + (c - '0');
			}
			int floatPow = pow(10, floatTally);
			floatValue /= floatPow;
			*pn = *pn + floatValue;
			*pn = *pn * sign;
		}
		if (c != EOF)
		{
			ungetch(c);
		}
		return *pn;
	}
	else /* else if no '+' or '-' char was encountered */
	{
		for (*pn = 0; isdigit(c); c = getch()) /* accumulate digits proper */
		{
			*pn = 10 * *pn + (c - '0');
		}
		if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') /* check for invalid characters */
		{
			ungetch(c);
			return 0;
		}
		if(c == '.') /* if a decimal point was encountered */
		{
			while (isspace(c = getch())) /* skip anymore wspace */
			{
				ungetch(c);
			}
			for (floatValue = 0.0, floatTally = 0.0; isdigit(c); c = getch(), floatTally++) /* get digits after decimal-point */
			{
				floatValue = 10 * floatValue + (c - '0');
			}
			if (c != EOF)
			{
				ungetch(c);
			}
			
			int floatPow = pow(10, floatTally);
			floatValue /= floatPow;
			*pn = *pn + floatValue;
			*pn = *pn * sign;
		}
		if (c != EOF)
		{
			ungetch(c);
		}
		return *pn;
	}
}

