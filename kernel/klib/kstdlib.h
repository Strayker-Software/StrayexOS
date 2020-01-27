/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel Standard Library file, functions in file "kstdlib.c"
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KSTDLIB_
#define _KSTDLIB_

#include <stdbool.h>

extern unsigned char kinportb (unsigned short _port);
extern void koutportb (unsigned short _port, unsigned char _data);
extern void kswap(int* a, int* b);
extern void kreverse(char str[]);
extern char *kitoa(int value, char *str, int base);
extern void pit_init(); // in "pit.c",
extern void Int_on();
extern void Int_off();

#endif
