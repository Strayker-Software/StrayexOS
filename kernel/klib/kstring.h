#ifndef _KSTRING_
#define _KSTRING_

extern int kstrlen(unsigned char *x);
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

#endif
