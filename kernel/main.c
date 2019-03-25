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
	which have to be 0x36D76289.
	*/

	// Loading value from EAX register to magic:
	int magic = 0;
	asm("movl %%EAX, %0;" : "=r" (magic));

	// For Multiboot Informations Structure address:
	struct multiboot_tag *mbi = 0;
	unsigned wiel;
	
	// Perform check operation:
	if(magic == MULTIBOOT2_BOOTLOADER_MAGIC)
	{ // MULTIBOOT2_BOOTLOADER_MAGIC is defined in multiboot.h in klib

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
	wiel = *(unsigned *)mbi; // Information structure size,
	unsigned char bootloader[100]; // Bootloader name,
	unsigned char args[100]; // CMD arguments,
	
	// RAM:
	unsigned int ram_mb =  0; // RAM amount in MB,
	unsigned int ram_kb = 0; // RAM amount in KB,
	unsigned int frames = 0; // RAM frames amount,

	// Memory map:
	multiboot_memory_map_t *mem; // Address to memory map,

	for (mbi = (struct multiboot_tag *) (mbi + 8); mbi->type != MULTIBOOT_TAG_TYPE_END; mbi = (struct multiboot_tag *) ((multiboot_uint8_t *) mbi + ((mbi->size + 7) & ~7)))
	{
		switch(mbi->type)
		{
			case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: ;
				//struct multiboot_tag_string *x;
				//x = (struct multiboot_tag_string *)mbi;
				//help = x->string;
				//memcpy((unsigned char *)bootloader, (const unsigned char *)help, kstrlen((unsigned char *)help) + 1);
				kprintf("BOOTLOADER: OK\n");
				//multiboot_string_t *x = (multiboot_string_t *)mbi;
				//memcpy(bootloader, (const unsigned char *)x->string, kstrlen((unsigned char *)x->string));
			break;
			
			case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: ;
				//struct multiboot_tag_basic_meminfo *y;
				//y = (struct multiboot_tag_basic_meminfo *)mbi;
				//unsigned int p = ((struct multiboot_tag_basic_meminfo *) mbi)->mem_lower;
				//unsigned int o = ((struct multiboot_tag_basic_meminfo *) mbi)->mem_upper;
				kprintf("MEMINFO: OK\n");
				//char poml[] = { };
				//kitoa(p, poml, 10);
				//kprintf(poml);
				//ram_kb = p + o;
				//ram_mb = ram_kb / 1024 + 2;
				//frames = ram_kb / 4;
			break;
			
			case MULTIBOOT_TAG_TYPE_CMDLINE: ;
				kprintf("CMDLINE: OK\n");
				//struct multiboot_tag_string *z;
				//z = (struct multiboot_tag_string *)mbi;
				//help = z->string;
				//memcpy(args, (const unsigned char *)help, kstrlen((unsigned char *)help) + 1);
			break;
		}
	}

	// Checks, if kernel have to write initailisation info on screen:
	if(if_info_on_screen)
	{
		// Writting the info:
		char pom[1000];
		kitoa((int)mbi, pom, 16);
		kprintf("MBI address: 0x");
		kprintf(pom);
		memset((unsigned char *)pom, ' ', 1000);
		kprintch('\n');
		kprintf("MBI size: ");
		kitoa(wiel, pom, 10);
		kprintf(pom);
		memset((unsigned char *)pom, ' ', 1000);
		kprintf(" B\n");
		kprintf("Bootloader: ");
		kprintf((char *)bootloader);
		kprintch('\n');
		kprintf("RAM: ");
		kitoa(ram_kb, pom, 10);
		kprintf(pom);
		memset((unsigned char *)pom, ' ', 1000);
		kprintf(" KB, ");
		kitoa(ram_mb, pom, 10);
		kprintf(pom);
		memset((unsigned char *)pom, ' ', 1000);
		kprintf(" MB, ");
		kitoa(frames, pom, 10);
		kprintf(pom);
		memset((unsigned char *)pom, ' ', 1000);
		kprintf(" frames\n");
		kprintf("Memory map:\n");
		for(mem = ((struct multiboot_tag_mmap *) mbi)->entries; (multiboot_uint8_t *) mem < (multiboot_uint8_t *) mbi + mbi->size; mem = (multiboot_memory_map_t *) ((unsigned long) mem + ((struct multiboot_tag_mmap *) mbi)->entry_size))
		{
			int i = 1;
			kitoa(i, pom, 10);
			kprintf(pom);
			memset((unsigned char *)pom, ' ', 1000);
			kprintf(". ");
			kprintf(" Address: 0x");
			multiboot_uint32_t pom1 = (mem->addr >> 32) + (mem->addr & 0xFFFFFFFF);
			kitoa(pom1, pom, 16);
			kprintf(pom);
			memset((unsigned char *)pom, ' ', 1000);
			kprintf(", length: 0x");
			pom1 = (mem->len >> 32) + (mem->len & 0xFFFFFFFF);
			kitoa(pom1, pom, 16);
			kprintf(pom);
			memset((unsigned char *)pom, ' ', 1000);
			kprintf(", type: 0x");
			kitoa(mem->type, pom, 10);
			kprintf(pom);
			memset((unsigned char *)pom, ' ', 1000);
			kprintf("\n");
			i++;
		}
		kprintf("Arguments for Strayex: ");
		kprintf((char *)args);
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
