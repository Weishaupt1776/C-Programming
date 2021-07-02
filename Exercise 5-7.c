/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Rewrite readlines to
 * store lines in an array supplied by main, rather than calling
 * alloc to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

/* macros */
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define BUFFER 10000

/* global variables */
char *lineptr[MAXLINES]; /* pointers to text lines */

/* functions */
int readlines(char *lineptr[], char inputbuffer[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getinput(char *line, int limit);
void swap(char *v[], int i, int j);

/* sort input lines */
int main(void)
{
	int nlines; /* number of input lines read */
	char inputbuffer[BUFFER];
	clock_t beginning, end;
	
	beginning = clock(); /* gather processing time before beginning work */
	if ((nlines = readlines(lineptr, inputbuffer, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		clock_t end = clock();
		printf("Total processor time: %f\n", (double)(end - beginning) / CLOCKS_PER_SEC);
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
		return 1;
	}
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
