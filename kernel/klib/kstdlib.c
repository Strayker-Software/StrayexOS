/*
 Strayex Kernel C Library "klib"
 v1.0
 Kernel Standard Library file, access through "kstdlib.h"
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "kstdlib.h"

// Reading from I/O ports:
unsigned char kinportb (unsigned short _port)
{
	unsigned char rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

// Writting from I/O ports:
void koutportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
