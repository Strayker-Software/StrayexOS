/*
 Strayex Kernel C Library "klib"
 v1.0.1
 Kernel memory managment functions and memory manager, header.
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KMEM_
#define _KMEM_

#include <stdbool.h>

extern bool mem_init(unsigned int ram_in_kb);
extern void *kmalloc(int size);
extern void kfree(void *addr);

#endif