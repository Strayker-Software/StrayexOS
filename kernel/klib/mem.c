/*
 Strayex Kernel C Library "klib"
 v1.0.1
 Kernel memory managment functions and memory manager, simple WatreMark manager.
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "kstring.h"
#include "kmem.h"
#include <stdbool.h>
#include "kstddef.h"

unsigned short *start_mem = (unsigned short *)0x300000; // Start free memory at 3MB tag, after kernel and shell,
unsigned short *curr_mem = (unsigned short *)0x200000; // Holds current memory, starts at 2MB tag for shell mapping, will be updated in functions,
unsigned int ram_kb = 0; // All avilable ram,

// Initialise memory manager:
bool mem_init(unsigned int ram_in_kb)
{
	ram_kb = ram_in_kb;
	return true;
}

// Allocates memory of given size:
void *kmalloc(int size)
{
	// First, function have to check, if we've got free memory. If not, inform caller by returning NULL.
	if(ram_kb == (int)*curr_mem)
	{
		// We have free memory!
		*curr_mem = size; // Move value to free space,
		// Update address to free space:
		curr_mem = (unsigned short *)(curr_mem + 0x000001);
        // Return old address, with allocated memory:
        return (void *)(curr_mem - 0x000001);
	}
	else
	{
		// No free memory! Inform caller!
		return NULL;
	}
	
	return NULL;
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
	curr_mem = (unsigned short *)(curr_mem - 0x000001);
}