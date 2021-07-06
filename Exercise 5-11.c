/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Modify the programs
 * entab and detab (written as exercises in Chapter 1) to accept a list
 * of tab stops as arguments. Use the default tab settings if there are
 * no arguments.
 */
 
/* This program solution was inspired by the user: Elyasin
 * https://github.com/Elyasin/K-and-R-solutions
 * Took part of his ideas and added some slight modifications,
 * credit is given to Elyasin for great assistance! */
 
#include <stdio.h>
#include <ctype.h>

/* macro definitions */
#define MAXLENGTH 1000 /* maximum length of input */
#define TABINDEX 8 /* where tab stop is found */
#define TABSTOP 1 /* tab stop found  */
#define NTABSTOP 0 /* no tab */

/* functions */
void entab(char to[], char from[]);
void detab(char to[], char from[]);
int getinput(char s[], int lim);
int settab(int argc, char *argv[], char tabarr[]);
int tabpos(int pos, char tabarr[]);
int atoi(char s[]);

/* holds the indexes of the tabstops 
 * borrowed from Elyasin */
char tabarr[MAXLENGTH]; 

int main(int argc, char *argv[])
{
	int validityTest, len;
	char line[MAXLENGTH];
	char entabbed_line[MAXLENGTH];
	char detabbed_line[MAXLENGTH];
	
	if ((validityTest = settab(argc, argv, tabarr)) == -1)
	{
		printf("terminating program\n");
		return -1;
	}
	
	while ((len = getinput(line, MAXLENGTH)) > 0) 
	{
        entab(entabbed_line, line);
        printf("%s", entabbed_line);
    }
    
    while ((len = getinput(line, MAXLENGTH)) > 0) 
	{
        detab(detabbed_line, line);
        printf("%s", detabbed_line);
    }
     
	return 0; /* execution successful */
}

/* entab: borrowed from Elyasin
 * https://github.com/Elyasin/K-and-R-solutions/blob/master/Exercise%205-11/entab.c */
void entab(char to[], char from[]) 
{
    int c, i, j, tabs, spaces, pos;

    spaces = tabs = 0;
    for (i = j = pos = 0; (c = from[i]) != EOF && c != '\n'; i++, pos++) 
    {
        if (c == ' ') 
        {
            //if ((pos + 1) % TABSTOP == 0) {
            if ( tabpos(pos+1, tabarr) == TABSTOP ) 
            {
                tabs++;
                spaces = 0;
            } 
            else 
            {
                spaces++;
            }
        }
        if (c != ' ') 
        {
            for (; tabs > 0; tabs--, j++)
                to[j] = '\t';
            tabs = 0;
            if (c == '\t') 
            {
                spaces = 0;
                //pos = pos + (TABSTOP - pos % TABSTOP) - 1;
                for ( ; tabarr[pos+1] != TABSTOP; pos++, j++) 
                {
                    to[j] = ' ';
                }
            }
            for (; spaces > 0; spaces--, j++)
                to[j] = ' ';
            to[j++] = c;
        }
    }
    if (c == '\n') 
    {
        to[j++] = c;
    }
    to[j] = '\0';
}

/* detab: function borrowed from Elyasin, 
 * https://github.com/Elyasin/K-and-R-solutions/blob/master/Exercise%205-11/detab.c*/
void detab(char to[], char from[])
{
	int c, i, k, pos; /* i is index of from[], k is index of to[], pos is index of tabarr[] */

    pos = 0;
    for (i = 0, k = 0; (c = from[i]) != EOF && c != '\n'; ++i, ++k) 
    {
        if (c == '\t') 
        {
            do
            {
				to[k++] = ' ';
			} while (tabpos(++pos, tabarr) == NTABSTOP); /* input space to next tab stop */
			k--; /* forces input to begin at tab stop */
        } 
        else 
        {
            to[k] = c;
            ++pos;
        }
    }
    if (c == '\n') 
    {
        to[k++] = c;
	}
    to[k] = '\0';
}

int tabpos(int pos, char tabarr[]) 
{
    if (pos >= MAXLENGTH)
    {
        return TABSTOP;
	}
    else
    {
        return tabarr[pos];
	}
}

/* getinput: this is the getline() function in the book "The C Programming Language" */
int getinput(char s[], int lim) 
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}

/* settab: sets tab stops at appropriate indexes and returns -1 if non-digit character was encountered at command-line */
int settab(int argc, char *argv[], char tabarr[])
{
	char *p = *++argv; /* points to **argv, and parses it to check for invalid characters */
	int pos = 0, index = 0; /* index of tabarr*/
	
	tabarr[index++] = NTABSTOP;
	
	if (argc <= 1) /* if there is only 1 argument, then mark tabs standardly */
	{
		for (; index < MAXLENGTH; index++)
		{
			if (index % TABSTOP == 0)
			{
				tabarr[index] = TABSTOP;
			}
			else
			{
				tabarr[index] = NTABSTOP;
			}
		}
		
		return 0; /* tab stops successfully set */
	}
	else
	{
		for (; index < MAXLENGTH; index++) /* initialize all tabarr[] to having no tab stops */
		{
			tabarr[index] = NTABSTOP;
		}
		
		while (--argc > 0) /* while there are still arguments on command-line */
		{
			while (*p) /* while the location in memory which 'p' points to is not NULL */
			{
				if (!isdigit(*p)) /* if the character which 'p' points to is not a digit */
				{
					printf("error: invalid input at command-line\n");
					return -1;
				}
				else
				{
					*p++; /* move 'p' to point to next character */
				}
			}
			
			++p; /* increment 'p' to point to next argument */
			pos = atoi(*argv); /* set pos to the number at current argv argument */
			++argv; /* point to next argument at command-line */
			if (pos > 0 && pos < MAXLENGTH)
			{
				tabarr[pos] = TABSTOP;
			}
			
		}
		
		return 0; /* tab stops successfully found*/
	}
}

int atoi(char s[])
{
	int i, n, sign;
	
	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}
