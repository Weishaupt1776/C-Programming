/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. As written, getint treats
 * a + or - not followed by a digit as a valid representation of zero.
 * Fix it to push such a character back on the input.
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

/* global variables */
int buf[BUFSIZE];
int bufp = 0;

/* functions */
int getch(void);
void ungetch(int c);
int getint(int *pn);

int main(void)
{
	int x;
	x = getint(&x);
	printf("The value of \"x\" is: %i\n", x);
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
int getint(int *pn)
{
	/* sign determines if neg or pos, c holds last char from stdin */
	int c, sign;
	
	/* skip white space */
	while (isspace(c = getch())) 
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		while (isspace(c = getch())) 
			ungetch(c);
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return *pn;
}

