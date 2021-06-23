/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Modify getop so that it
 * doesn't need to use ungetch. Hint: use an internal static variable.
 *
 */


#include <stdio.h>
#include <ctype.h>

/* symbolic constants */
#define MAXOP 100 /* max size of operand or operator*/
#define NUMBER '0' /* signal that number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100 /* buffer size */

/* external variables */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

void push(double f);
double pop(void);
int getch(void);
int getop(char s[]);
double atof(char s[]);


int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	
	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0)
					push((int)pop() % (int)op2);
				else
					printf("error: cannot mod with 0 divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
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
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
		
}

/* pop: pop and return value from stack */
double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getch(void) /* get a (possibly pushed back) character */
{
	return getchar();
}

/* getop: get next operator, numeric operand, variable, or math function */
int getop(char s[])
{
	/* 'i' is variable for s[] index, 'c' is variable for most recently pushed back character */
	int i, c;
	static int buf = EOF;
	
	i = 0; /* index is set to 0 */
	if(buf != EOF)
	{
		s[i] =  buf;
		buf = EOF;
	}
	
	/* skips any blanks until first non-blank is encountered */
	while((s[i] = c = getch()) == ' ' || c == '\t')
	{
		continue;
	}
	s[++i] = '\0';
	
	if(c == '-' || c == '+')
	{
		/* local variable holding previous char */
		int prevchar = c;
		
		/* if next char is not a digit or a decimal point */
		if(!isdigit(c = getch()) && c != '.')
		{
			buf = c; /* ungetch */
			return prevchar;
		}
		
		/* collect valid integer portion */
		if(isdigit(c))
		{
			s[i] = c;	
			while(isdigit(s[++i] = c = getch()))
			{
				continue;
			}
		}
		
		/* collecting fractional part */
		if(c == '.') 
		{
			s[i] = c;
			while(isdigit(s[++i] = c = getch()))
			{
				continue;
			}
		}
		s[i] = '\0';
		
		if(c != EOF)
		{
			buf = c; /* ungetch */
		}
		return NUMBER;
	}
	
	else
	{
		if(!isdigit(c) && c != '.')
		{
			return c;
		}
		if(isdigit(c))
		{
			while(isdigit(s[i++] = c = getch()))
			{
				continue;
			}
		}
		if(c == '.')
		{
			while(isdigit(s[i++] = c = getch()))
			{
				continue;
			}
		}
		s[--i] = '\0';
		
		if(c != EOF)
		{
			buf = c; /* ungetch */
		}
		return NUMBER;
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
