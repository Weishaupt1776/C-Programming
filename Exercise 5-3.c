/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a pointer version
 * of the function strcat that we showed in chapter 2: strcat(s,t)
 * copies the string t to the end of s.
 */
 
 /* The pre-requisite for solving this problem is to make sure
  * that the resultant string or character array will be big
  * enough to hold the characters for both inputs! */


#include <stdio.h>
#define MAXCHARS 100

void strcatPointer(char *t, char *f);

int main(void)
{
	char t[MAXCHARS] = "No! ";
	char f[MAXCHARS] = "This is Patrick!\n";
	strcatPointer(t,f);
	printf("%s\n", t);
	return 0;
}

/* strcat: copies string f 'from' to string t 'to' */
void strcatPointer(char *t, char *f)
{
	/* moves pointer 't' to end of itself */
	while(*t)
		t++;
	while((*t++ = *f++)) /* copies 'f' to 't' */
		continue;
}

