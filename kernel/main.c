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

	// Multiboot informations:
	char *bootloader = (char *)mbi->boot_loader_name; // Bootloader name,
	char *args = (char *)mbi->cmdline; // CMD arguments,

	// RAM:
	unsigned int ram_mb = mbi->mem_upper / 1024 + 2; // RAM amount in MB,
	unsigned int ram_kb = ram_mb * 1024; // RAM amount in KB,
	unsigned int frames = ram_kb / 4; // RAM frames amount,

	// Memory map:
	multiboot_memory_map_t *mem = (multiboot_memory_map_t *)mbi->mmap_addr; // Address to memory map,

	// Checks, if kernel have to write initailisation info on screen:
	if(if_info_on_screen)
	{ // TODO: Memory map loading is not working well!
		// Writting the info:
		kprintf("Bootloader: ");
		kprintf(bootloader);
		kprintch('\n');
		char pom[] = { };
		kprintf("RAM: ");
		kitoa(ram_mb, pom, 10);
		kstrcpyw(pom);
		kprintf(pom);
		kprintf(" MB\n");
		kprintf("Memory map:\n");
		kprintf("Map address: 0x");
		kitoa(mbi->mmap_addr, pom, 16);
		kprintf(pom);
		kprintf(", map length: ");
		kitoa(mbi->mmap_length, pom, 10);
		kprintf(pom);
		kprintf(" B\n");
		for(int i = 1; (unsigned int)mem < mbi->mmap_addr + mbi->mmap_length; i++)
		{
			kitoa(i, pom, 10);
			kprintf(pom);
			kprintf(". Size: ");
			kitoa(mem->size, pom, 10);
			kstrcpyw(pom);
			kprintf(pom);
			kprintf(" B, address: 0x");
			unsigned int pom1 = mem->addr_up + mem->addr_low;
			kitoa(pom1, pom, 16);
			kprintf(pom);
			kprintf(", length: 0x");
			pom1 = mem->len_up + mem->len_low;
			kitoa(pom1, pom, 16);
			kprintf(pom);
			kprintf(", type: 0x");
			kitoa(mem->type, pom, 16);
			kprintf(pom);
			kprintf("\n");
			mem = (multiboot_memory_map_t *)((unsigned int)mem + mem->size + sizeof(unsigned int));
		}
		kprintf("Arguments for Strayex: ");
		kprintf(args);
		kprintch('\n');
	}

	gdt_init(); // Mapping General Descriptor Table,
	idt_init(); // Mapping Interrupt Descriptor Table,
	isrs_init(); // Mapping Interrupt Service Routains,
	irq_init(); // Remapping IDT and ISRs for working properly with IRQs,
	pit_init(); // Mapping IRQ0 for Programmable Interval Timer,
	kb_init(); // Mapping PS/2 keyboard driver,

	Int_on(); // Enable interrupts,

	/*
	Special variable for checking, if descriptor tables are working, if you want to check that,
	uncomment next two lines. This checking controls GDT, IDT, ISRs and IRQs.
	*/

	//int a = 10;
	//int b = a / 0;

	// After startup of system with it, screen shoud contain "Division By Zero Exception. System Halted!"

	// Initialisation complete! Start main kernel function:
	kmain();
}
