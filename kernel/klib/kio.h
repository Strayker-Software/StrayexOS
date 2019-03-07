/*
 Strayex Kernel C Library "klib"
 v1.0
 Kernel Input / Output file, functions in file kernel's drivers
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KIO_
#define _KIO_

extern void kprintch(unsigned char x);
extern void kprintf(char *x);
extern void kmove_cursor();
extern void ksetattrib(char font, char bg);
extern void kcls();

#endif
