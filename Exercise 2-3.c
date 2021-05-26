/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write the function
 * htoi(s) which converts a string of hexadecimal digits (including
 * an optional 0x or 0X) into its equivalent integer value. The
 * allowable digits are 0 to 9, a through f, and A through F.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "get.h"

enum hexadecimal { A = 10, B = 11, C = 12, D = 13, E = 14, F = 15 };
int hexDigitEval(char hexadecimalCharacter);
int power(int base, int exponent);
int htoi(char* hexString);

int main(void)
{
	string hexString = get_string();
	htoi(hexString);
	return 0;
}

int hexDigitEval(char hexadecimalCharacter)
{
	int hexadecimalVal;
	if(hexadecimalCharacter == '0')
	{
		hexadecimalVal = 0;
	}
	else if(hexadecimalCharacter == '1')
	{
		hexadecimalVal = 1;
	}
	else if(hexadecimalCharacter == '2')
	{
		hexadecimalVal = 2;
	}	
	else if(hexadecimalCharacter == '3')
	{
		hexadecimalVal = 3;
	}
	else if(hexadecimalCharacter == '4')
	{
		hexadecimalVal = 4;
	}
	else if(hexadecimalCharacter == '5')
	{
		hexadecimalVal = 5;
	}
	else if(hexadecimalCharacter == '6')
	{
		hexadecimalVal = 6;
	}
	else if(hexadecimalCharacter == '7')
	{
		hexadecimalVal = 7;
	}
	else if(hexadecimalCharacter == '8')
	{
		hexadecimalVal = 8;
	}
	else if(hexadecimalCharacter == '9')
	{
		hexadecimalVal = 9;
	}
	else if(hexadecimalCharacter == 'A' || hexadecimalCharacter == 'a')
	{
		hexadecimalVal = A;
	}
	else if(hexadecimalCharacter == 'B' || hexadecimalCharacter == 'b')
	{
		hexadecimalVal = B;
	}
	else if(hexadecimalCharacter == 'C' || hexadecimalCharacter == 'c')
	{
		hexadecimalVal = C;
	}
	else if(hexadecimalCharacter == 'D' || hexadecimalCharacter == 'd')
	{
		hexadecimalVal = D;
	}
	else if(hexadecimalCharacter == 'E' || hexadecimalCharacter == 'e')
	{
		hexadecimalVal = E;
	}
	else if(hexadecimalCharacter == 'F' || hexadecimalCharacter == 'f')
	{
		hexadecimalVal = F;
	}
	
	return hexadecimalVal;
}

int power(int base, int exponent)
{
	int result = base;
	
	if(exponent == 0)
		return 1;
	else
	{
		for(int i = 1; i < exponent; i++)
		{
			result *= base;
		}
	}
	return result;
}

int htoi(char* hexString)
{
	unsigned short hexStringSize = strlen(hexString);
	int hexTotalValue = 0;
	int hexIndex;
	int hexDigit;
	
	
	/* lines 21-68 focus on validating a valid hexadecimal string */
	if(hexString[0] == '0')
	{
		if(hexStringSize == 1)
		{
			printf("error: need to input more valid characters\n");
			printf("returning -1\n");
			return -1;
		}
		if(hexString[1] == 'x' || hexString[1] == 'X')
		{
			for(int i = 2; i < hexStringSize; i++)
			{
				if((hexString[i] >= 'A' && hexString[i] <= 'F') || (hexString[i] >= 'a' && hexString[i] <= 'f') || (hexString[i] >= '0' && hexString[i] <= '9'))
				{
					; // do nothing
				}
				else
				{
					printf("error: invalid hexadecimal string format\n");
					printf("returning -1\n");
					return -1;
				}
			}
		}
		else if(hexString[1] != 'X' || hexString[1] != 'x')
		{
			printf("error: invalid hexadecimal string format\n");
			printf("returning -1\n");
			return -1;
		}
	}
	else if(hexString[0] != '0')
	{
		// parse through string to verify it as a valid hex
		for(int i = 0; i < hexStringSize; i++)
		{
			if((hexString[i] >= 'A' && hexString[i] <= 'F') || (hexString[i] >= 'a' && hexString[i] <= 'f') || (hexString[i] >= '0' && hexString[i] <= '9'))
			{
				; // do nothing
			}
			else
			{
				printf("error: invalid hexadecimal string format\n");
				printf("returning -1\n");
				return -1;
			}
		}
	}
	
	/* Calculating decimal value of hexidecimal string */
	for(int i = hexStringSize-1, exp = 0; i >= 0; i--, exp++)
	{
		if(hexString[i] == 'x' || hexString[i] == 'X')
		{
			printf("The value of hexadecimal string is: %i\n", hexTotalValue);
			return 0;
		}
		else if(hexString[i] != 'x' || hexString[i] != 'X')
		{
			hexDigit = hexDigitEval(hexString[i]);
			hexIndex = power(16, exp);
			hexTotalValue += hexDigit * hexIndex;
		}
	}
	printf("Total hexadecimal string value: %i\n", hexTotalValue);
	
	return hexTotalValue;
}
