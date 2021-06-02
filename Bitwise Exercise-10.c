/* C program to count leading zeros in a binary number 
 * https://codeforwin.org/2016/01/c-program-to-count-leading-zeros-in-binary-number.html
 * Write a C program to input any number from user and find total number of leading zeros of the given number.
 */

#include <stdio.h>
#define INT_SIZE sizeof(int) * 8

int main()
{
    int num, count, msb, i;

    /* Input number from user */
    printf("Enter any number: ");
    scanf("%d", &num);

    // Equivalent to
    // 10000000 00000000 00000000 00000000
    msb = 1 << (INT_SIZE - 1);

    count = 0;

    /* Iterate over each bit */
    for(i=0; i<INT_SIZE; i++)
    {
        /* If leading set bit is found */
        if((num << i) & msb)
        {
            /* Terminate the loop */
            break;
        }

        count++;
    }

    printf("Output leading zeros: %d", count);

    return 0;
}
