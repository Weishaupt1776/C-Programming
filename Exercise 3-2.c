/* This is a program in the book "The C Programming Language" by
 * Brian W. Kernighan and Dennis M. Ritchie. Write a function
 * escape(s,t) that converts characters like newline and tab into
 * visible escape sequences like \n and \t as it copies the string
 * t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences into the real characters. 
 */


#include <stdio.h>
#define MAXLINE 1000

void getinput(char t[], int limit);
void escape(char s[], char t[]);
void escapeReverse(char s[], char t[]);

int main(void)
{
	char s[MAXLINE], t[MAXLINE];
	getinput(t, MAXLINE-1);
	escape(s,t);
	printf("%s\n", s);
	escapeReverse(s,t);
	printf("%s\n", s); 
	return 0;
}

void getinput(char t[], int limit)
{
	int c, i;
	
	for(i = 0; i<limit-1 && (c = getchar()) != EOF; i++)
	{
		t[i] = c;
	}
	t[i] = '\0';
}

void escape(char s[], char t[])
{
	int index_s, index_t;
	index_s = index_t = 0;
	
	while(t[index_t] != '\0')
	{
		switch(t[index_t])
		{
			case '\n':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 'n';
				index_s++;
				index_t++;
				break;
			case '\t':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 't';
				index_s++;
				index_t++;
				break;
			case '\a':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 'a';
				index_s++;
				index_t++;
				break;
			case '\b':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 'b';
				index_s++;
				index_t++;
				break;
			case '\f':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 'f';
				index_s++;
				index_t++;
				break;
			case '\v':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 'v';
				index_s++;
				index_t++;
				break;
			case '\r':
				s[index_s] = '\\';
				index_s++;
				s[index_s] = 'r';
				index_s++;
				index_t++;
				break;
			default:
				s[index_s] = t[index_t];
				index_t++;
				index_s++;
				break;
		}
	}
	s[index_s] = '\0';
}

void escapeReverse(char s[], char t[])
{
	int index_s, index_t;
	index_s = index_t = 0;
	
	while(t[index_t] != '\0')
	{
		switch(t[index_t])
		{
			case '\\':
				switch(t[++index_t])
				{
					case 'n':
						s[index_s] = '\n';
						index_s++;
						index_t++;
						break;
					case 't':
						s[index_s] = '\t';
						index_s++;
						index_t++;
						break;
					case 'v':
						s[index_s] = '\v';
						index_s++;
						index_t++;
						break;
					case 'b':
						s[index_s] = '\b';
						index_s++;
						index_t++;
						break;
					case 'r':
						s[index_s] = '\r';
						index_s++;
						index_t++;
						break;
					case 'a':
						s[index_s] = '\a';
						index_s++;
						index_t++;
						break;
					case 'f':
						s[index_s] = '\f';
						index_s++;
						index_t++;
						break;
					default:
						s[index_s] = t[index_t];
						index_t++;
						index_s++;
						break;
				}
			default:
				s[index_s] = t[index_t];
				index_t++;
				index_s++;
				break;
		}
	}
	s[index_s] = '\0';
}
