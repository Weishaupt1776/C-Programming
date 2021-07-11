/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Add the option -f to fold
 * upper and lower case together, so that case distinctions are not
 * made during sorting; for example, a and A compare equal.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

/* global variables */
char *lineptr[MAXLINES]; /* pointers to text lines */
static int numeric = 0; /* determines if 'numcmp' function will be used or 'strcmp' */
static int reverse = 0; /* determines if function will be sorted in reverse order */
static int fold = 0; /* determines if function will fold so 'a' and 'A' are equal */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* postion in allocbuf */

/* global functions */
int setflags(int argc, char *argv[]);
int getinput(char *line, int limit);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
double atof(char s[]);
void qsort(void *lineptr[], int left, int right,
int (*comp) (void *, void *));


int main(int argc, char *argv[])
{
	int nlines, flagcheck;
	
	if ((flagcheck = setflags(argc,argv)) == -1) /* sets appropriate flags for program, also checks for appropriate input */
	{
		printf("terminating program\n");
		return -1;
	}
	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		qsort((void **) lineptr, 0, nlines-1,
		(int (*)(void*, void*))(numeric ? (char*)numcmp : (char*)strcmp));
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("input too big to sort\n");
		return 1;
	}
}

int setflags(int argc, char *argv[])
{
	char *p = *++argv; /* create a 'pointer to char' and set it argv[1] */
	
	if (argc <= 1)
	{
		return 0; /* signal that function executed successfully */
	}
	else if (argc > 1)
	{	
		while (--argc > 0) /* while there are still arguments */
		{	
			if ((*p) != '-') /* make sure that first character encountered is proper '-' */
			{
				printf("error: invalid format for flag\n");
				return -1;
			}
			*p++;
			
			while (*p) /* while NULL has not been reached */
			{
				switch (*p)
				{
					case 'n':
						numeric = 1;
						*p++;
						break;
					case 'r':
						reverse = 1;
						*p++;
						break;
					case 'f':
						fold = 1;
						*p++;
						break;
					default:
						printf("error: invalid format for flag\n");
						return -1;
						break;
				}
			}
			p = *++argv; /* point to next command-line argument */
		}
	}
	return 0; /* signal that function executed succesfully */
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

/* alloc: return pointer to n characters */
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n)
	{
		allocp += n;
		return allocp - n;
	}
	else
	{
		return 0;
	}
		
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	
	nlines = 0;
	while ((len = getinput(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
		{
			return -1;
		}
		else
		{
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
void swap(void *v[], int i, int j)
{
	char *temp;
	
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;
	
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power;
	int i, sign;
	
	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val /power;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
int (*comp) (void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);
	
	if (left >= right) /* do nothing if array contains fewer than two elements */
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
	{
		if (fold == 1)
		{
			char *p = (char*)v[i];
			
			while (*p) /* while there is characters in the string */
			{
				if (isupper(*p))
				{
					*p = (*p) + 32;
				}
				*p++;
			}
			
			p = (char*)v[left];
			while (*p) /* while there is characters in the string */
			{
				if (isupper(*p))
				{
					*p = (*p) + 32;
				}
				*p++;
			}
			
		}
		if (reverse == 1)
		{
			if ((*comp)(v[i], v[left]) > 0)
			{
				swap(v, ++last, i);
			}
		}
		else
		{
			if ((*comp)(v[i], v[left]) < 0)
			{
				swap(v, ++last, i);
			}
		}
	}
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}
