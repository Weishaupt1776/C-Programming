/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write the program
 * expr, which evaluates a reverse Polish expression from the command
 * line, where each operator or operand is a separate argument.
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER 0

double stack[MAXOP];
int sp = 0;

void push(double f);
double pop(void);
double atof(char s[]);

int main(int argc, char *argv[])
{	
	/* local variables */
	char *p; /* read the string in char **argv */
	int index, c; /* holds index, and most recent char */
	char s[MAXOP]; /* char array to hold different types of input */
	int type; /* determines category of input */
	double op2; /* for division and subtraction */
	
	
	/* check for valid argument count */
	if (argc <= 1) 
	{
		printf("error: need more arguments for calculation\n");
		return -1;
	}
	
	for (int i = 1; i < argc; i++) /* parse through arguments */
	{
		getop:
			index = 0; /* initialize parser, and test values */
			++argv; /* get argv to point to proper inital argument */
			p = *argv; /* p points to actual string to parse it */
			
			if (*argv == NULL)
			{
				printf("\t%.8g\n", pop());
				return 0;
			}
		
			while ((c = *p++)) /* parse through all characters in string */
			{
				if ((!isdigit(c)) && (c != '+' && c != '-' && c != '*' && c != '/')) /* check for invalid characters */
				{
					printf("error: not in valid format\n");
					return -1;
				}
			}
			p = *argv; /* reset p to parse through string again, and save to 'c' */
			c = *p;
		
			if (isdigit(c)) /* if a digit was encountered */
			{
				while (isdigit(c))
				{
					s[index++] = c;
					c = *++p;
				}
				s[index] = '\0';
				type = NUMBER;
				goto calculation;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/')
			{
				s[index++] = c;
				s[index] = '\0';
				type = c;
				goto calculation;
			}
	}
	
	calculation:
		switch (type)
		{
			case NUMBER:
				push(atof(s));
				goto getop;
				break;
			case '+':
				push(pop() + pop());
				goto getop;
				break;
			case '*':
				push(pop() * pop());
				goto getop;
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				goto getop;
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				goto getop;
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	
	return 0;
}

/* push: push f onto value stack */
void push(double f)
{
	if(sp < MAXVAL)
		stack[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
		
}

/* pop: pop and return value from stack */
double pop(void)
{
	if(sp > 0)
		return stack[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power;
	int i, sign;
	
	for(i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	
	return sign * val / power;
}

