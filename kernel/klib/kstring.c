/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel String file, access through "kstring.h"
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved

 https://overiq.com/c-programming-101/the-strcpy-function-in-c/
*/

#include <stdbool.h>
#include "kstring.h"

// Counts letters in given string:
int kstrlen(unsigned char *x)
{
	int i = 0;
	for(;x[i] != '\0';) i++;
	return i;
}

// Checks, that given string is valid ASCII string type:
bool StringChecker(char *ret)
{
	int n = kstrlen((unsigned char *)ret);
	for(int i = 0; i < n; i++)
	{
		if(!(ret[i] >= ' ' && ret[i] <= '~')) return false;
	}

	if(ret[n + 1] != '\0') return false;

	return true;
}

// Copies count bytes from src to dest, returning dest address:
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for( ; count != 0; count--) *dp++ = *sp++;
	return dest;
}

// Fills bytes of data in memory:
unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
	char *temp = (char *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

// Same as above, but working on 16-bit val:
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
	unsigned short *temp = (unsigned short *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}

// Cuts last char from char array:
char *kstrcpyw(char *src)
{
	int n = kstrlen((unsigned char *)src);
	src[n - 1] = '\0';
	memcpy((unsigned char *)src, (const unsigned char *)src, n - 1);
	return src;
}

// Copies source string to destination:
char *kstrcpy(char *src, char *dest)
{
    char *start = dest;
 
    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
 
    *dest = '\0';
    return start;
}

// Connects second string on the end of first, ANSI C standard:
char *kstrcat(char *s, const char *ct)
{ // TODO: test it!
	int s_length = kstrlen((unsigned char *)s);
	int ct_length = kstrlen((unsigned char *)ct);
	
	int i = s_length;
	int j = 0;
	for(; i <= ct_length; i++)
	{
		s[i] = ct[j];
		j++;
	}
	s[i + 1] = '\0';
	
	return s;
}
