/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel Input / Output file, functions in kernel's drivers
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KIO_
#define _KIO_

#include <stdbool.h>

extern void kprintch(char x); // in screen.c
extern void kprintf(const char *x, ...); // in screen.c
extern int kprintint(int x, int base); // in screen.c
extern void kmove_cursor(int x, int y); // in screen.c
extern void ksetattrib(char font, char bg); // in screen.c
extern void kcls(); // in screen.c
extern void kb_init(); // in keyboard.c
extern void kb_install(int x); // in keyboard.c
extern void enable_cursor(unsigned char cursor_start, unsigned char cursor_end); // in screen.c
extern void disable_cursor(); // in screen.c
extern void kbflush(); // in keyboard.c
extern char *get_kb_buf(); // in keyboard.c
extern bool kb_status(); // in keyboard.c
extern void set_kb_status(bool x); // in keyboard.c
extern bool kb_buf_status(); // in keyboard.c
extern void set_kb_buf_status(bool x); // in keyboard.c
extern int get_cursor_x(); // in screen.c
extern int get_cursor_y(); // in screen.c
extern unsigned char *get_layout(); // in keyboard.c
extern char get_last_char(); // in keyboard.c
extern void setCaps(bool x); // in keyboard.c
extern bool getCapsStatus(); // in keyboard.c

#endif
