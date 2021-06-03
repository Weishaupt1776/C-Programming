/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Our binary search makes
 * two tests inside the loop, when only one would suffice (at the price
 * of more tests outside). Write a version with only one test inside
 * the loop and measure the difference in run-time. */

#include <stdio.h>
#include <time.h>

int newbinsearch(int x, int v[], int n); // my written function
int oldbinsearch(int x, int v[], int n); // K&R function

int main(void)
{
	// declares necessary variables and arrays
	int x = 700200, n = 1000000;
	int v[n];
	
	// assigns values to array v[] in ascending order
	for(int i = 0, index = 0; i < n; i+=2, index++)
	{
		v[index] = i;
	}
	
	newbinsearch(x, v, n);
	oldbinsearch(x, v, n);
	return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] 
 * this is the binsearch I wrote myself */
int newbinsearch(int x, int v[], int n)
{
	clock_t runtime = clock();
	int low, high, mid; // local variable declaration
	
	low = 0; // set initial lowest index
	high = n - 1; // set initial highest index
	mid = (low+high) / 2; // set initial mid index
	
	while((x != v[mid]) && (low <= high))
	{
		if(x > v[mid])
		{
			low = mid+1; // sets new low
			mid = (low+high) / 2; // sets new mid
		}
		else
		{
			high = mid-1; // sets new high
			mid = (low+high) / 2; // sets new mid
		}
	}
	
	if(x == v[mid])
	{
		runtime = clock() - runtime;
		printf("Runtime clocks: %f\nRuntime seconds: %f\n", (float)runtime, (float)runtime / CLOCKS_PER_SEC);
		return mid; // returns index with value
	}
	else
	{
		runtime = clock() - runtime;
		printf("Runtime clocks: %f\nRuntime seconds: %f\n", (float)runtime, (float)runtime / CLOCKS_PER_SEC);
		return -1; // x value was not found in v[]
	}
}


/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] 
 * this binsearch is an example in the book The C Programming
 * Language by Dennis Ritchie and Brian W. Kernighan */
int oldbinsearch(int x, int v[], int n)
{
	clock_t runtime = clock();
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(x < v[mid])
		{
			high = mid - 1;
		}
		else if(x > v[mid])
		{
			low = mid + 1;
		}
		else
		{
			runtime = clock() - runtime;
			printf("Runtime clocks: %lu\nRuntime seconds: %lu\n", (unsigned long)runtime, (unsigned long)runtime / CLOCKS_PER_SEC);
			return mid;
		}
	}
	
	runtime = clock() - runtime;
	printf("Runtime clocks: %lu\nRuntime seconds: %lu\n", (unsigned long)runtime, (unsigned long)runtime / CLOCKS_PER_SEC);
	return -1;
}
