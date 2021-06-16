/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Add access to library
 * functions like sin, exp, and pow. See math.h in Appendix B, Section
 * 4.
 */

/* I just found out that on a linux computer the standard
 * C math library is not automatically linked. Therefore, I had to
 * compile this program separately using the shell and the command
 * gcc "Exercise 4-5.c" -o "Exercise 4-5.o" -lm */
 
 /* The C exp function is one of the Math Functions, 
  * used to return E raised to the power of a given value or specified 
  * expression. Here, E is Euler’s number, and it is approximately equal
  * to 2.71828.
  */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/* symbolic constants */
#define MAXOP 100 /* max size of operand or operator*/
#define NUMBER '0' /* signal that number was found */
#define IDENTIFIER '1' /* signal that math function input */
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
void showTop(void);
void duplicate(void);
void swapItems(void);
void clearStack(void);
void trig(char s[]);


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
			case IDENTIFIER:
				trig(s);
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
                		clearStack();
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
	s[1] = '\0';
	
	/* gathers input to test if sin(), cos(), or pow() were input*/
	if(isalpha(c))
   {
      i = 0;
      while(isalpha(s[i++] = c ))
         c = getch();     
      s[i - 1] = '\0';
      if(c != EOF)
         ungetch(c);
      return IDENTIFIER;
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

void clearStack(void)
{
    sp = 0;
}

/* function for math */
/* deal with a string/name this may be either a maths function or for
future exercises: a variable */
void trig(char s[])
{
   double op2;
   
   if( 0 == strcmp(s, "sin"))
      push(sin(pop()));
   else if( 0 == strcmp(s, "cos"))
      push(cos(pop()));
   else if (0 == strcmp(s, "exp"))
      push(exp(pop()));
   else if(!strcmp(s, "pow"))
   {
      op2 = pop();
      push(pow(pop(), op2));
   }
   else
      printf("%s is not a supported function.\n", s);
}
