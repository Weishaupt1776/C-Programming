/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. An alternate organization
 * uses getline to read an entire input line; this makes getch() and
 * ungetch() unnecessary. Revise the calculator to use this approach.
 *
 */
 
/* I had to rename function getline() to getlineinput() because 
 * in my system the stdio.h file already has a function defined as
 * getline() and compiling caused some error to occur */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* symbolic constants */
#define MAXOP 100 /* max size of operand or operator*/
#define NUMBER '0' /* signal that number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100 /* buffer size */

/* external variables */
int sp = 0; /* next free stack position */
double stack[MAXVAL]; /* value stack */
char calculation[MAXOP];
int calIndex = 0; /* current position in s[] */

/* external functions */
int getop(char s[]);
void push(double f);
double pop(void);
int getlineinput(char s[], int lim);
void clearStacks(char s[]);
void clearbuf(char calculation[]);
double atof(char s[]);

/* reverse Polish calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	
	clearStacks(s);
	
	while((type = getlineinput(s, MAXOP-1)) > 0)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(calculation));
				clearbuf(calculation);
				break;
			case '+':
				push(pop() + pop());
				clearbuf(calculation);
				break;
			case '*':
				push(pop() * pop());
				clearbuf(calculation);
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				clearbuf(calculation);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				clearbuf(calculation);
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				clearStacks(s);
				calIndex = 0;
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
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

int getlineinput(char s[], int lim)
{
	/* declare array for storing proper operand or operators */
	int cindex = 0;
	
	/* getline() function is here */	
	if(s[calIndex] == '\0')
	{
		int i, c;
		for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		{
			s[i] = c;
		}
		if(c == '\n')
		{
			s[i] = c;
			++i;
		}
		s[i] = '\0';
	}
	
	/* skip all wspace */
	while((s[calIndex]) == ' ' || s[calIndex] == '\t')
	{
		calIndex++;
	}
	calculation[cindex] = s[calIndex];
	calIndex++;
	
	/* if not a valid number */
	if(!isdigit(calculation[cindex]) && calculation[cindex] != '.')
	{
		return calculation[cindex]; /* not a number */
	}
	
	/* collect integer part */
	if(isdigit(s[calIndex]))
	{
		cindex++;
		while(isdigit(s[calIndex]))
		{
			calculation[cindex++] = s[calIndex++];
		}
	}
	
	/* collect fractional part */
	if(s[calIndex] == '.')
	{
		calculation[++cindex] = s[calIndex++];
		cindex++;
		
		while(isdigit(s[calIndex]))
		{
			calculation[cindex++] = s[calIndex++];
		}
	}
	
	
	return NUMBER;
	
}

void clearStacks(char s[])
{
	int i;
	
	for(i = 0; i < MAXVAL; i++)
	{
		s[i] = '\0';
		calculation[i] = '\0';
		stack[i] = 0.0;
	}
}

void clearbuf(char calculation[])
{
	int i;
	
	for(i = 0; i < MAXVAL; i++)
	{
		calculation[i] = '\0';
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
