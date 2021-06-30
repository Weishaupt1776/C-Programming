/*  This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write versions of the 
 * library functions strncpy, strncat, and strncmp, which operate
 * on at most the first n characters of their argument strings.
 * For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B. */


#include <stdio.h>
#include <string.h>
#define MAXCHARS 100


void strncpyVer2(char *t, char *f, int n);
void strncatVer2(char *t, char *f, int n);
int strncmpVer2(char *t, char *f, int n);

int main(void)
{
	return 0;
}

/* strncpyVer2: copies at most n chars from 'f' to 't' */
void strncpyVer2(char *t, char *f, int n)
{
	int length = strlen(f);
	
	if (length < n)
	{
		for (int i = 0; i < length; i++)
		{
			*t++ = *f++;
		}
		*t = '\0';
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			*t++ = *f++;
		}
		*t = '\0';
	}
}

/* strncatVer2: copies n chars from the string f to the end of t */
void strncatVer2(char *t, char *f, int n)
{
	/* get length of string 'f' */
	int length = strlen(f);
	
	/* moves pointer 't' to end of itself */
	while(*t)
		t++;
	if (length < n)
	{
		for (int i = 0; i < length; i++)
		{
			*t++ = *f++;
		}
		*t = '\0';
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			*t++ = *f++;
		}
		*t = '\0';
	}
}

/* strncmp: compares the first n chars in 'f' with 't' */
int strncmpVer2(char *t, char *f, int n)
{
	for (int i = 0; i < n-1 && *t == *f; i++, t++, f++)
	{
		if (*t == '\0')
		{
			return 0;
		}
	}
	return *t - *f;
}
