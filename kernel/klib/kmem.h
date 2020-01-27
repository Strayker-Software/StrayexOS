/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel memory managment functions and memory manager, header. Functions im "mem.c"
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KMEM_
#define _KMEM_

#include <stdbool.h>

extern bool mem_init(unsigned int mem_length);
extern void *kmalloc(int size);
extern void kfree(void *addr);

#endif
