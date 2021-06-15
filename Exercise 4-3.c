/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Given the basic framework,
 * it's straightforward to extend the calculator. Add the modulus(%)
 * operator and it's provisions for negative numbers.
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
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* external functions */
int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);
double atof(char s[]);

/* reverse Polish calculator */
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
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	i = 0;
	
	/* skips any blanks until first non-blank is encountered */
	while((s[i] = c = getch()) == ' ' || c == '\t')
	{
		continue;
	}
	
	/* gather total input */
	if(s[i] == '-' || s[i] == '+')
	{
		/* collect valid integer portion */
		while(isdigit(s[++i] = c = getch()))
		{
			continue;
		}
		/* test if input had a valid digit */
		if(!isdigit(s[i-1]) && !isdigit(s[i]))
		{
			ungetch(c);
			return s[i-1]; // not a format number
		}
		/* collecting fractional part */
		if(s[i] == '.') 
		{
			/* test if input had a valid digit */
			if(!isdigit(s[i-1]))
			{
				printf("error: improper format\n");
				return c; // not a format number
			}
			while(isdigit(s[++i] = c = getch()))
			{
				continue;
			}
		}
		s[i] = '\0';
		if(c != EOF)
		{
			ungetch(c);
		}
		return NUMBER;
	}
	else
	{
		s[1] = '\0';
		if(!isdigit(c) && c != '.')
			return c; /* not a number */
		if(isdigit(c)) /* collect integer part */
			while(isdigit(s[++i] = c = getch()))
				;
		if(c == '.') /* collect fraction part */
			while(isdigit(s[++i] = c = getch()))
				;
		s[i] = '\0';
		if(c != EOF)
			ungetch(c);
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
