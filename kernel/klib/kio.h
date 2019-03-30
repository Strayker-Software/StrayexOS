/*
 Strayex Kernel C Library "klib"
 v1.0.0
 Kernel Input / Output file, functions in kernel's drivers
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KIO_
#define _KIO_

#include <stdbool.h>

extern void kprintch(char x);
extern void kprintf(const char *x, ...);
extern int kprintint(int x, int base);
extern void kmove_cursor(int x, int y);
extern void ksetattrib(char font, char bg);
extern void kcls();
extern void kb_init();
extern void kb_install(int x);
extern void enable_cursor(unsigned char cursor_start, unsigned char cursor_end);
extern void disable_cursor();
extern void kbflush();
extern char *get_kb_buf();
extern bool kb_status();
extern void set_kb_status(bool x);
extern bool kb_buf_status();
extern void set_kb_buf_status(bool x);
extern int get_cursor_x();
extern int get_cursor_y();
extern unsigned char *get_layout();
extern char get_last_char();

#endif
