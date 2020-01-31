/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel String file, functions in file "kstring.c"
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KSTRING_
#define _KSTRING_

extern int kstrlen(unsigned char *x);
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern char *kstrcpyw(char *src);
extern char *kstrcpy(char *src, char *dest);
extern char *kstrcat(char *s, const char *ct);

#endif
