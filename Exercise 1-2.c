/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Experiment to find out
 * what happens when printf's argument string contains \c, where c
 * is some character not listed above.
 */
 
 /* Since the publication of this book, the escape sequence \c is 
  * no longer part of the language. Experimenting with other
  * escape sequences in this program.
  */

#include <stdio.h>

int main(void)
{
	printf("Hello, my fellow problem-solver\n");
    return (0);
}
