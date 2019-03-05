/*
 Strayex Kernel C Library "klib"
 v1.0
 Kernel Standard Library file, functions in file "kstdlib.c"
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KSTDLIB_
#define _KSTDLIB_

extern unsigned char kinportb (unsigned short _port);
extern void koutportb (unsigned short _port, unsigned char _data);

#endif
