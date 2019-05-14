/*
 Strayex Kernel C Library "klib"
 v1.0.1
 Kernel memory managment functions, with "liballoc" support.
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "liballoc.h"
#include "kstdlib.h"
#include "kstring.h"

// Locks environment for memory allocation:
int liballoc_lock()
{
	Int_off();
	
	return 0;
}

// Unlocks environment after memory allocation:
int liballoc_unlock()
{
	Int_on();
	
	return 0;
}

// Allocates given amount of pages in memory:
void *liballoc_alloc(int pages)
{
	unsigned int size = pages * 4096;
	char *p = (char *)malloc(size);
	if(!p) return NULL;
	else return p;
}

// Releases given space:
int liballoc_free(void* addr, int pages)
{ // Need to check this!
	int x = pages * 4096;
	while(x != 0)
	{
		free(addr);
		x -= 4096;
	}
	return 0;
}