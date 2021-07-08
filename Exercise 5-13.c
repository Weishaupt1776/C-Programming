/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write the program tail,
 * which prints the last 'n' lines of its input. By default, n is 10,
 * let us say, but it can be changed by an optional argument, so that
 * tail -n prints the last n lines. The program should behave rationally
 * no matter how unreasonable the input or the value of n. Write the
 * program so it makes the best use of available storage; lines should
 * be stored as in sorting program of Section 5.6, not in a two-dimensional
 * array of fixed size.
 */

/* standard header files */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* macros */
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define BUFFER 10000

/* global variables */
char *lineptr[MAXLINES]; /* pointers to text lines */
char *tailedlines[MAXLINES];

/* functions */
int readlines(char *lineptr[], char inputbuffer[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getinput(char *line, int limit);
void swap(char *v[], int i, int j);
void copytail(char *to[], int nlines, int n);
int setn(int argc, char *argv[]);
int atoi(char s[]);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines, n; /* number of input lines read, and number of tailed-lines */
	char inputbuffer[BUFFER]; /* buffer to hold characters */
	
	if ((n = setn(argc, argv)) == -1) /* make sure n is valid */
	{
		printf("terminating program\n");
		return -1;
	}
	while ((nlines = readlines(lineptr, inputbuffer, MAXLINES)) >= 0 &&  nlines < MAXLINES-1)
	{
		/* do nothing */;
	}

	copytail(tailedlines, nlines, n); /* copy last 'n' lines to tailedlines[] */
	
	if (n <= nlines)
	{
		qsort(tailedlines, 0, n-1); /* sorts the respective lines into alphabetical order */
		writelines(tailedlines, n); /* print last 'n' lines */
	}
	else if (n > nlines)
	{
		qsort(tailedlines, 0, nlines-1); /* sorts the respective lines into alphabetical order */
		writelines(tailedlines, nlines); /* print last 'n' lines */
	}
	return 0;
}

/* getinput: read a line into 'line', return length */
int getinput(char *line, int limit)
{
	int c, i;
	
	for (i = 0; i < limit-1 && (c = getchar()) != EOF && c != '\n'; ++i)
	{
		line[i] = c;
	}
	if (c == '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return i;
}

/* readlines: read input lines */
int readlines(char *lineptr[], char inputbuffer[], int maxlines)
{
	int len, nlines;
	char *p, *bufp, line[MAXLEN];
	
	bufp = inputbuffer;
	nlines = 0;
	while ((len = getinput(line, MAXLEN)) > 0)
		if (nlines >= maxlines)
		{
			printf("error: maxlines exceeded\n");
			return -1;
		}
		else if ((inputbuffer + BUFFER - bufp) < len)
		{
			printf("error: not enough room\n");
			return 0;
		}
		else
		{
			bufp += len;
			p = bufp-len;
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;
	
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* copy last 'n' text lines from old array to new array */
void copytail(char *to[], int nlines, int n)
{
	int parser = 0, count = 0; /* will make sure we copy appropriate text-lines */
	char **p = lineptr; /* set 'p' to point to first character pointer in lineptr[] */
	
	/* copy last 'n' lines if 'n' is less than or equal to nlines */
	if (n <= nlines-1)
	{
		while (parser < nlines-1)
		{
			p++;
			parser++;
		}
		
		/* copy last 'n' text-lines to new array */
		while (count < n)
		{
			to[count++] = *p--;
		}
	}
	else if (n > nlines-1) /* else if n > nlines, copy all lines */
	{
		while (count < nlines-1)
		{
			to[count++] = *p;
			p++;
		}
	}
	
}

/* settab: sets n to appropriate index with command-line */
int setn(int argc, char *argv[])
{
	char *p = *argv; /* points to **argv, and parses it to check for invalid characters */
	int pos = 0;
	
	if (argc <= 1) /* if there is only 1 argument, then mark tabs standardly */
	{
		return 10;
	}
	else if (argc == 2 && *argv[1] == '-') 
	{
		p = argv[1]; /* set p to argv[1] or second argument */
		*p++;
		
		while (*p)
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
		pos = atoi(&(*++argv)[1]); /* returns digit */
		return pos;
	}  
	else
	{
		printf("error: invalid input at command-line\n");
		return -1;
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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	
	if (left >= right) /* do nothing if array contains */
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}
