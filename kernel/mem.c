/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel memory managment functions and memory manager, simple WaterMark manager.
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kstring.h"
#include "klib/kmem.h"
#include <stdbool.h>
#include <stddef.h>

unsigned short *StartMem = (unsigned short *)0x00200000; // Start position of manager,
unsigned short RamLength = 0x0; // How much RAM does kernel have?

// Initialise memory manager:
bool mem_init(unsigned int mem_length)
{
	RamLength = mem_length; // Set length of available RAM,
	
	return true;
}

// Allocates memory of given size, if allocation is not possible, returns NULL:
void *kmalloc(int size)
{
	// First, function have to check, if we've got free memory. If not, inform caller by returning NULL.
	if((unsigned int)(*StartMem + size) < RamLength)
	{ // Free memory here!
		// Update address to move memory pointer:
		StartMem = (unsigned short *)(StartMem + size);
		
        // Return old address, pointing allocated memory block:
        return (void *)(StartMem - size);
	}
	else
	{
		// No free memory! Inform caller!
		return NULL;
	}
}

// Allocates memory for given elements and given size, if allocation is not possible, returns NULL:
void *kcalloc(size_t nobj, size_t size)
{
	size_t how_much_to_alloc = size * nobj;
	int *addr = kmalloc(how_much_to_alloc);
	
	for(int i = *addr + 1; (size_t)addr != (size_t)StartMem - 0x1; i++) addr[i] = 0;
	
	return addr;
}

// Frees block of memory in given address:
void kfree(void *addr)
{
	// First, we have to check how many memory we have to free:
	int size = sizeof(addr);
	// If block is free already:
	if(size <= 0) return;
	// Else let's free this block of memory:
	memset(addr, 0, size);
	// Move back pointer of taken memory, to use this address again:
	StartMem = (unsigned short *)(StartMem - size);
}