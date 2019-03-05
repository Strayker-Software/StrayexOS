/*
	Copyright 2019 Daniel Strayker Nowak
	All rights reserved
*/

#include <stdint.h>
#include <stdbool.h>
#include "klib/multiboot.h"
#include "klib/kio.h"
#include "klib/kstring.h"

bool if_info_on_screen = true;

// Main kernel's function, loading and running Strayex Shell:
void kmain()
{
	for(;;);
}

// This function manipulate Multiboot informations and initialise the kernel's modules:
void kinit()
{
	/*
	Let's initialise kernel to work properly.
	First of all, we have to check, if Strayex Kernel was loaded by Multiboot boot loader (like GRUB).
	If it's true, we can use Multiboot Information Structure, which is loaded to the memory,
	pointed by physical address in EBX register.
	We can check Multiboot booting up by reading value from EAX register,
	which have to be 0x2BADB002.
	*/

	// Loading value from EAX register to magic:
	int magic = 0;
	asm("movl %%EAX, %0;" : "=r" (magic));

	// For Multiboot Informations Structure address:
	multiboot_info_t *mbi;
	
	// Perform check operation:
	if(magic == MULTIBOOT_BOOTLOADER_MAGIC)
	{ // MULTIBOOT_BOOTLOADER_MAGIC is defined in multiboot.h in klib

		// Yes, Strayex Kernel booted by Multiboot boot loader!

		// Loading physical address of Multiboot Informations Structure to mbi pointer:
		asm("movl %%EBX, %0;" : "=r" (mbi));
	}
	else
	{
		// No, Strayex Kernel booted with no-Multiboot!
	}

	// Checks, if kernel have to write initailisation info on screen:
	if(if_info_on_screen)
	{
		kprintf("StrayexOS "); // My name :)
		kprintf((char *)mbi->boot_loader_name); // Bootloader
	}

	// Initialisation complete! Start main kernel function:
	kmain();
}
