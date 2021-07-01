/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Rewrite appropriate 
 * programs from earlier chapters and exercises with pointers instead
 * of array indexing. Good possibilities include getline (Chapters 1 and 4),
 * atoi, itoa, and their variants (Chapter 2, 3, and 4), reverse (Chapter 3),
 * and strindex and getop (Chapter 4)
 */

/* All function in the problem synopsis have been rewritten
 * using pointers instead of array indexes, which is not a very
 * far leap as far as difficulty */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* symbolic constants */
#define MAXCHARS 100 /* max characters for character array */
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER 0 /* signal that number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100 /* buffer size */

/* external variables */
int sp = 0; /* next free stack position for value stack */
double val[MAXVAL]; /* value stack for varibles to do calculation */
char buf[BUFSIZE]; /* buffer for ungetch to push back input */
int bufp = 0; /* next free position in buf */

int getinput(char *s, int limit);
int atoi(char *s);
void strngcpy(char *t, char *f);
void reverse(char *s);
void itoa(int n, char *s);
int stringdex(char *s, char *t);
void ungetch(int c);
int getch(void);
int getop(char *s);

int main(void)
{
	char s[MAXCHARS];
	getop(s);
	return 0;
}

/* getinput: variation of getline reads a line into *s. return length */
int getinput(char *s, int limit)
{
	int c, i;
	
	for (i = 0; i < limit-1 && (c = getchar()) != EOF && c != '\n'; s++, i++)
		*s = c;
	if (c == '\n')
	{
		*s = c;
		s++;
		++i;
	}
	*s = '\0';
	return i;
}

/* atoi: convert *s to integer */
int atoi(char *s)
{
	int i, n, sign;
	
	for (i = 0; isspace(*s); i++, s++) /* skip white space */
		;
	sign = (*s == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
	{
		s++;
		i++;
	}
	for (n = 0; isdigit(*s); i++, s++)
		n = 10 * n + (*s - '0');
	return sign * n;
}

/* strncpy: copy *f to *t */
void strngcpy(char *t, char *f)
{
	while ((*t++ = *f++))
		continue;
}

/* reverse: reverse *s in place */
void reverse(char *s)
{
	int length = strlen(s)-1;
	char temp[MAXCHARS]; /* creates a temp array to hold copy of *s */
	char *tp = temp; /* creates a temporary pointer */
	
	strngcpy(temp,s); /* copies the contents of *s into temp */
	
	for (int i = 0; i < length; i++, tp++)
		continue; /* moves pointer *tp to end of input */
	
	for (int i = 0; i <= length; i++, s++, tp--)
	{
		*s = *tp;
	}
	
}

/* itoa: convert n to characters in *s */
void itoa(int n, char *s)
{
	char *copy = s;
	int sign;
	
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	
	do /* generate digits in reverse order */
	{
		*s = n % 10 + '0';
		s++;
	} while ((n /= 10) > 0);
	if (sign < 0)
	{
		*s = '-';
		s++;
	}
	*s = '\0';
	reverse(copy);
}

/* stringdex: return index of t in s, -1 if none */
int stringdex(char *s, char *t)
{
	/* counter for inner index */
	int i, k;
	
	for (i = 0; *s; s++, i++)
	{
		for (k = 0; *t && *s == *t; k++, t++)
			;
		if (k > 0 && *t == '\0')
			return i;
	}
	return -1;		
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getch(void) /* get a possibly pushed back character */ 
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* getop: get next operator, numeric operand, variable, or math function */
int getop(char *s)
{	
	while ((*s = getch()) == ' ' || *s == '\t')
		;
	*(++s) = '\0';
	if (!isdigit(*s) && *s != '.')
		return *s;
	if (isdigit(*s))
		while (isdigit(*(s++) = getch()))
			;
	*s = '\0';
	if (*s != EOF)
		ungetch(*s);
	return NUMBER;
}

