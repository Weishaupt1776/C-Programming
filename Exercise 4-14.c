/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Define a macro swap(t,x,y)
 * that interchanges two arguments of type t.
 */
 
/* Credit given to Gregory Pietsch 
 * https://penti.org/~sederlok/misc/lang/c/the_c_programming_language_-_exercises/krx414.html */

#include <stdio.h>

#define swap(t,x,y) do{t z=x;x=y;y=z;}while(0)
#define PRINTVAR(X) printf(#X);

int main(void)
{
	double a = 10.5;
	double b = 5.2;
	printf("A = %f\tB = %f\n", a, b);
	swap(double, a, b);
	printf("A = %f\tB = %f\n", a, b);
	return 0;
}

