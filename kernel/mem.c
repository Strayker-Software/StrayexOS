/*
 Strayex Kernel C Library "klib"
 v1.0.1
 Kernel memory managment functions and memory manager, simple WaterMark manager.
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kstring.h"
#include "klib/kmem.h"
#include "klib/kstddef.h"
#include <stdbool.h>

unsigned short *StartMem = (unsigned short *)0x00200000; // Start position of manager,
unsigned short RamLength = 0x0; // How much RAM does kernel have?

// Initialise memory manager:
bool mem_init(unsigned int mem_length)
{
	RamLength = mem_length; // Set length of available RAM,
	
	return true;
}

// Allocates memory of given size:
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

// Frees block of memory in given address:
void kfree(void *addr)
{
	// First, we have to check how many memory we have to free:
	int size = (int)addr;
	// If block is free already:
	if(size <= 0) return;
	// Else let's free this block of memory:
	memset(addr, 0, size);
	// Move back pointer of taken memory, to use this address again:
	StartMem = (unsigned short *)(StartMem - 0x000001);
}