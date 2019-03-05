/*
 Strayex Kernel C Library "klib"
 v1.0
 Kernel String file, access through "kstring.h"
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "kstring.h"

// Counts letters in given string:
int kstrlen(unsigned char *x)
{
	int i = 0;
	for(;x[i] != '\0';) i++;
	return i;
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
