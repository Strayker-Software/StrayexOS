/*
 Strayex Kernel C Library "klib"
 v1.0
 Kernel Input / Output file, functions in file kernel's drivers
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KIO_
#define _KIO_

extern void kprintch(char x);
extern void kprintf(const char *x, ...);
extern int kprintint(int x, int base);
extern void kmove_cursor(int x, int y);
extern void ksetattrib(char font, char bg);
extern void kcls();
extern void kb_init();
extern void enable_cursor(unsigned char cursor_start, unsigned char cursor_end);
extern void disable_cursor();
// TODO: funkcje z keyboard.c

#endif
