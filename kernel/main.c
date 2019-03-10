/*
 Strayex Kernel
 v1.0
 Kernel's main file, with kinit and kmain functions
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include <stdint.h>
#include <stdbool.h>
#include "klib/multiboot.h"
#include "klib/kio.h"
#include "klib/kstring.h"
#include "klib/kstdlib.h"
#include "klib/kdt.h"

// Holds information, if kernel have to show loading info on screen, default is true,
bool if_info_on_screen = true;

// Main kernel's function, loading and running Strayex Shell (not yet):
void kmain()
{
	// Here before for loop you can add your own code to make Strayex Kernel do something extra for you!

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
	multiboot_info_t *mbi = 0;
	
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
		kprintf("Fatal Error - Strayex booted by no-Multiboot bootloader!\n");
		kprintf("Terminating...");
		return;
	}

	kprintf("StrayexOS\n"); // My name :) for information, that Strayex is loading now,

	// Checks, if kernel have to write initailisation info on screen:
	if(if_info_on_screen)
	{
		// Writting the info:
		kprintf("Bootloader: ");
		kprintf((char *)mbi->boot_loader_name);
		kprintch('\n');
		kprintf("Lower memory: ");
		char hel[] = { };
		kitoa(mbi->mem_lower, hel, 10);
		kprintf(hel);
		kprintf(" KB\n");
		kprintf("Upper memory: ");
		kitoa(mbi->mem_upper, hel, 10);
		kprintf(hel);
		kprintf(" KB\n");
		kprintf("Arguments for Strayex: ");
		kprintf((char *)mbi->cmdline);
		kprintch('\n');
	}

	gdt_init(); // Mapping General Descriptor Table,

	// Initialisation complete! Start main kernel function:
	kmain();
}
