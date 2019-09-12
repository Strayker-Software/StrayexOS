/*
 Strayex Kernel C Library "klib"
 v1.0.1
 Kernel Debug Functions, functions in file "debug.c"
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KDEBUG_
#define _KDEBUG_

extern void init_serial();
extern int is_transmit_empty();
extern void write_serial(char a);
extern void DebugWrite(char *x);

#endif
