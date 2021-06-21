/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Add commands for handling
 * variables. (It's easy to provide twenty-six variables with 
 * single-letter names.) Add a variable for the most recently printed
 * value.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/* symbolic constants */
#define MAXOP 100 /* max size of operand or operator*/
#define NUMBER 0 /* signal that number was found */
#define IDENTIFIER 1 /* signal that character string was input */
#define ENDSTRING 2
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100 /* buffer size */
#define MAXVARS 32 /* size of struct varType array in main */

/* external variables */
int sp = 0; /* next free stack position for value stack */
double val[MAXVAL]; /* value stack for varibles to do calculation */
char buf[BUFSIZE]; /* buffer for ungetch to push back input */
int bufp = 0; /* next free position in buf */
char varList[MAXVARS]; /* this is an array to store the list of single character variables */
double varValues[MAXVARS]; /* this is an array to store the corresponding values of character variables */
int varsIndex = 0; // current index of varList and varValues arrays
char recentVar;
double recentVal;

/* external functions */
int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);
double atof(char s[]);
void showTop(void);
void duplicate(void);
void swapItems(void);
void clearStacks();
void dealWithName(char s[]);
void dealWithVar(char s[]);

/* reverse Polish calculator */
int main(void)
{
	int type; /* determines if EOF value was encountered */
	double op2; /* variable for holding second operand for mathematical calculation like division or subtraction */
	char s[MAXOP]; /* string which holds max of 100 chars to turn into number or variable, or to perform math function */
	
	clearStacks(); /* effectively clears value stack before main work is done, and clears var[MAXVARS] array */
	
	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case IDENTIFIER:
				dealWithName(s);
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
			case '?':
				showTop();
                break;
            case '#':
                duplicate();
                break;
            case '~':
                swapItems();
                break;
            case '!':
                clearStacks();
                break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			case ENDSTRING:
				break;
			case '=':
				pop();
				varValues[varsIndex] = pop();
				recentVal = varValues[varsIndex];
				push(recentVal);
				break;
			case '<':
				printf("The last variable used was: \n");
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

/* getop: get next operator, numeric operand, variable, or math function */
int getop(char s[])
{
	/* 'i' is variable for s[] index, 'c' is variable for most recently pushed back character */
	int i, c;
	
	/* skips any blanks until first non-blank is encountered */
	i = 0; /* index is set to 0 */
	while((s[i] = c = getch()) == ' ' || c == '\t')
	{
		continue;
	}
	s[++i] = '\0';
	
	/*checks if s[i] was a character */
	if(isalpha(c))
	{
		while(isalpha(s[i++] = c = getch()))
		{
			continue;
		}
		s[--i] = '\0';
		
		if(c != EOF)
		{
			ungetch(c);
		}
		return IDENTIFIER;
	}
	
	if(c == '-' || c == '+')
	{
		/* local variable holding previous char */
		int prevchar = c;
		
		/* if next char is not a digit or a decimal point */
		if(!isdigit(c = getch()) && c != '.')
		{
			ungetch(c);
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
			ungetch(c);
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
			ungetch(c);
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

/* These functions were copied and retrieved from penti.org user Bob Wightman
 * https://penti.org/~sederlok/misc/lang/c/the_c_programming_language_-_exercises/krx404.html */

void showTop(void)
{
    if(sp > 0)
        printf("Top of stack contains: %8g\n", val[sp-1]);
    else
        printf("The stack is empty!\n");
}


void duplicate(void)
{
    double temp = pop();

    push(temp);
    push(temp);
}

void swapItems(void)
{
    double item1 = pop();
    double item2 = pop();

    push(item1);
    push(item2);
}

void clearStacks()
{
   /* clear the value stack by setting the pointer to the bottom. */
   sp = 0;
   
   /* clear variabe list by declaring each index in array to '\0' and corresponding values to 0.0 */
   for(int i = 0; i < MAXVARS-1; i++)
   {
	   varList[i] = '\0';
	   varValues[i] = 0.0;
   }
}

/* function for math */
/* deal with a string/name this may be either a maths function or for
future exercises: a variable */
/* a string/name may be either a maths function or a variable */
void dealWithName(char s[])
{
   double op2;
   
   if(0 == strcmp(s, "sin"))
      push(sin(pop()));
   else if(0 == strcmp(s, "cos"))
      push(cos(pop()));
   else if (0 == strcmp(s, "exp"))
      push(exp(pop()));
   else if(0 == strcmp(s, "pow"))
   {
      op2 = pop();
      push(pow(pop(), op2));
   }
   /* Finally if it isn't one of the supported maths functions we have a 
      variable to deal with. */
   else
   {
		dealWithVar(s);
   }
}

/* deals with variable name */
void dealWithVar(char s[])
{
	/* i is index, and j is inner loop index */
	int i, j;
	i = j = 0;
	
	/* check if variable has been saved already */
	while(s[i] != '\0')
	{
		while(varList[j] != '\0' && j < MAXVARS-1)
		{
			/* if character at s[i] == varList[j] */
			if(s[i] == varList[j])
			{
				recentVar = varList[j];
				recentVal = varValues[j];
				push(recentVal);
				return;
			}
			else
			{
				j++;
			}
		}
		
		j = 0; /* reset counter for j index */
		i++; /* increment i by 1 for next index in s[] */
	}
	
	i = 0; /* reset i index for parsing through s[] */
	j = 0; /* reset j index for parsing through varList[] */
	/* variable has not been found yet, so we will add it as well as corresponding value */
	while(s[i] != '\0')
	{
		/* locate next free index in varList[] */
		while(varList[j] != '\0')
		{
			j++; /* increment j to next index */
		}
		varList[j] = s[i]; /* assign varList[j] to character in s[i] */
		recentVar = varList[j]; /* */
		recentVal = varValues[j];
		varsIndex = j;
		push(recentVal);
		j = 0; /* reset index j */
		i++; /* increment index i for s[] */
	}
}
