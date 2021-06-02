/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a program entab
 * that replaces strings of blanks by the minimum number of tabs 
 * and blanks to achieve the same-spacing. Use the same tab stops
 * as for detab. When either a tab or a single blank would suffice to
 * reach a tab stop, which should be given preference?
 */
 
#include <stdio.h>
#include <ctype.h>
#define TAB 8
#define MAXLINE 1000

int getmine(char s[], int lim);
int entab(char output[], int pos, int space);

int main()
{
	return 0;
}
