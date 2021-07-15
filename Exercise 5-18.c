/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Made dcl recover from
 * input errors.
 */
 
 /* solution was based off and inspired by github user Elyasin 
  * https://github.com/Elyasin/K-and-R-solutions/blob/master/Exercise%205-18/decl.c
  * All proper thanks go to their respected source */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* global macros */
#define MAXTOKEN 100 /* maximum length of token */
#define BUFSIZE 100 /* maximum buffer capacity for getch() and ungetch() */

enum tokenclassification { NAME, PARENS, BRACKETS }; /* these enumeration constants are used in the function gettoken(). The values
 are repectively NAME = 0, PARENS = 1, and BRACKETS = 2. The respective value is assigned to the variable 'tokentype' 
 once the category of the token is classified, and then returned in the function gettoken(). */

/* global functions */
void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void ungetch(int c);
int is_valid_datatype(char *datatype);
void clearbuffers();

/* global variables and arrays */
int tokentype; /* token type classification */
char token[MAXTOKEN]; /* current character token from input */
char name[MAXTOKEN]; /* name of variable */
char datatype[MAXTOKEN]; /* data type of variable */
char out[1000]; /* character array which holds pointer to specifications */
char buf[BUFSIZE]; /* buffer to hold pushed-back character input from ungetch() */
int bufp = 0; /* int variable acts as the index to buf[] and displays total amount of pushed-back characters */


int main(void)
{
	resetInput:
		while (gettoken() != EOF) /* 1st token on line */
		{
			strcpy(datatype, token);
			if (!is_valid_datatype(datatype)) 
			{
				printf("error: datatype unknown %s\n", datatype);
				clearbuffers();
				goto resetInput;
			}
			else
			{
				out[0] = '\0';
				dcl();
				if (tokentype != '\n') 
				{
					printf("syntax error: %c\n", tokentype);
					while (gettoken() != '\n')
						;
				} 
				else
				{
					printf("%s %s %s\n", name, out, datatype);
				}
			}
		}
		return 0;
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;
	
	if (tokentype == '(') /* ( dcl ) */
	{
		dcl();
		if (tokentype != ')')
		{
			printf("error: missing )\n");
		}
	}
	else if (tokentype == NAME) /* variable name */
	{
		strcpy(name, token);
	}
	else
	{
		printf("error: expected name or (dcl)\n");
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if (type == PARENS)
		{
			strcat(out, " function returning");
		}
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;
	
	for (ns = 0; gettoken() == '*'; ) /* count *'s */
	{
		ns++;
	}
	dirdcl();
	while (ns-- > 0)
	{
		strcat(out, " pointer to");
	}
}

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
	if(bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters\n");
	}
	else
	{
		buf[bufp++] = c;
	}
}

/* gettoken: return tokentype */
int gettoken(void)
{
	int c; /* most recent character of input */
	char *p = token; /* points to the index 0 of token[]. */
	
	while ((c = getch()) == ' ' || c == '\t') /* get input from user using getch(), skip any white-space, stop when first
	non white-space is encountered */
		;
	if (c == '(') /* if c is an open parentheses */
	{
		if ((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
		
	}
	else if (c == '[') /* if c is an open bracket */
	{
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) /* if c is an alphabetical character */
	{
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else /* else, c is a miscellaneous character */
	{
		return tokentype = c;
	}
}

void clearbuffers()
{
	bufp = 0; /* reset bufp pointer */
	
	/* clears buffer used by gettoken() and getch() */
	while (gettoken() != '\n')
	{
		continue;
	}
	
	/* clear main arrays: "name", "datatype", "token", and "buf" */
	for (int i = 0; i < MAXTOKEN; i++)
	{
		name[i] = '\0';
		datatype[i] = '\0';
		token[i] = '\0';
		buf[i] = '\0';
	}
	
	/* clear "out" array */
	for (int i = 0; i < 1000; i++)
	{
		out[i] = '\0';
	}
	
}

int is_valid_datatype(char *datatype) 
{
    return strcmp(datatype, "char") == 0 || 
            strcmp(datatype, "short") == 0 ||
            strcmp(datatype, "int") == 0 || 
            strcmp(datatype, "long") == 0 ||
            strcmp(datatype, "float") == 0 ||
            strcmp(datatype, "double") == 0 ||
            strcmp(datatype, "void") == 0;
}
