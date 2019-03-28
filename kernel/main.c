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
void kinit(unsigned long magic, unsigned long mbi)
{
	/*
	Let's initialise kernel to work properly.
	First of all, we have to check, if Strayex Kernel was loaded by Multiboot boot loader (like GRUB).
	If it's true, we can use Multiboot Information Structure, which is loaded to the memory,
	pointed by physical address in EBX register.
	We can check Multiboot booting up by reading value from EAX register,
	which have to be 0x36D76289. That values are on stack and are provided in kinit's args.
	*/

	struct multiboot_tag *tag;
	unsigned wiel;
	
	// Perform check operation:
	if(magic == MULTIBOOT2_BOOTLOADER_MAGIC)
	{ // MULTIBOOT2_BOOTLOADER_MAGIC is defined in multiboot.h in klib
		// Yes, Strayex Kernel booted by Multiboot boot loader!
	}
	else
	{
		// No, Strayex Kernel booted with no-Multiboot!
		kprintf("Fatal Error - Strayex booted by no-Multiboot bootloader!\n");
		kprintf("Restart mashine!");
		return;
	}

	kprintf("StrayexOS\n"); // My name :) for information, that Strayex is loading now,
	
	// Multiboot informations:
	
	wiel = *(unsigned *)mbi; // Information structure size,
	unsigned char bootloader[100]; // Bootloader name,
	unsigned char args[100]; // CMD arguments,
	unsigned int driver = 0; // boot driver number,
	unsigned int partition = 0; // boot top-level partition number;
	unsigned int subpart = 0; // boot sub-level partition number;
	// RAM:
	unsigned int ram_mb =  0; // RAM amount in MB,
	unsigned int ram_kb = 0; // RAM amount in KB,
	unsigned int frames = 0; // RAM frames amount,
	// Memory map:
	multiboot_memory_map_t *mem; // Temporary address to memory map,
	multiboot_memory_map_t mem_tab[100]; // Save informations for memory manager,
	int mem_map_length = 0; // Length of memory map, for memory manager too,

	for (tag = (struct multiboot_tag *) (mbi + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7)))
	{
		switch(tag->type)
		{
			case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: ;
				multiboot_string_t *x = (multiboot_string_t *)tag;
				memcpy(bootloader, (const unsigned char *)x->string, kstrlen((unsigned char *)x->string));
			break;

			case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: ;
				unsigned int p = ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower;
				unsigned int o = ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper;
				ram_kb = p + o;
				ram_mb = ram_kb / 1024 + 1;
				frames = ram_kb / 4;
			break;

			case MULTIBOOT_TAG_TYPE_CMDLINE: ;
				for(int i = 0; i < 100; i++)
				{
					args[i] = '\0';
				}
				
				struct multiboot_tag_string *z;
				z = (struct multiboot_tag_string *)tag;
				int n = kstrlen((unsigned char *)z->string);
				memcpy(args, (const unsigned char *)z->string, n + 1);
				if(args[0] == '\0') memcpy(args, (const unsigned char *)"none\0", 5);
			break;
			
			case MULTIBOOT_TAG_TYPE_MMAP: ;
				for(mem = ((struct multiboot_tag_mmap *) tag)->entries; (multiboot_uint8_t *) mem < (multiboot_uint8_t *) tag + tag->size; mem = (multiboot_memory_map_t *) ((unsigned long) mem + ((struct multiboot_tag_mmap *) tag)->entry_size))
				{
					mem_tab[mem_map_length] = *mem;
					mem_map_length++;
				}
			break;
			
			case MULTIBOOT_TAG_TYPE_BOOTDEV: ;
				driver = ((struct multiboot_tag_bootdev *) tag)->biosdev;
				partition = ((struct multiboot_tag_bootdev *) tag)->slice;
				subpart = ((struct multiboot_tag_bootdev *) tag)->part;
			break;
		}
	}

	// Checks, if kernel have to write initailisation info on screen:
	if(if_info_on_screen)
	{
		// Writting the info:
		//char pom[1000];
		//kitoa((int)mbi, pom, 16);
		kprintf("MBI address: 0x%x\n", mbi);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		kprintf("MBI size: %i B\n", wiel);
		//kitoa(wiel, pom, 10);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		kprintf("Bootloader: %c\n", (char *)bootloader);
		//kprintf((char *)bootloader);
		//kprintch('\n');
		kprintf("RAM: %i KB, %i MB, %i frames\n", ram_kb, ram_mb, frames);
		//kitoa(ram_kb, pom, 10);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		//kprintf(" KB, ");
		//kitoa(ram_mb, pom, 10);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		//kprintf(" MB, ");
		//kitoa(frames, pom, 10);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		//kprintf(" frames\n");
		kprintf("Memory map:\n");
		for(int i = 0; i < mem_map_length; i++)
		{
			*mem = mem_tab[i];
			//kitoa(i + 1, pom, 10);
			char addr[1000];
			char len[1000];
			unsigned pom1 = mem->addr >> 32;
			unsigned pom2 = mem->addr & 0xFFFFFFFF;
			unsigned pom3 = mem->len >> 32;
			unsigned pom4 = mem->len & 0xFFFFFFFF;
			//memset((unsigned char *)pom, ' ', 1000);
			kitoa(pom1, addr, 16);
			kitoa(pom2, addr, 16);
			//memset((unsigned char *)pom, ' ', 1000);
			kitoa(pom3, len, 16);
			kitoa(pom4, len, 16);
			kprintf("%i. Address: 0x%c, Length: 0x%c, Type: 0x%i\n", i + 1, addr, len, mem->type);
			//memset((unsigned char *)pom, ' ', 1000);
			//kprintf("");
			//kitoa(pom1, pom, 16);
			//kprintf(pom);
			//memset((unsigned char *)pom, ' ', 1000);
			//kitoa(pom2, pom, 16);
			//kprintf(pom);
			//memset((unsigned char *)pom, ' ', 1000);
			//kprintf(", length: 0x");
			//pom1 = (mem->len >> 32);
			//pom2 = (mem->len & 0xFFFFFFFF);
			//kitoa(pom1, pom, 16);
			//kprintf(pom);
			//memset((unsigned char *)pom, ' ', 1000);
			//kitoa(pom2, pom, 16);
			//kprintf(pom);
			//memset((unsigned char *)pom, ' ', 1000);
			//kprintf(", type: 0x");
			//kitoa(mem->type, pom, 16);
			//kprintf(pom);
			//memset((unsigned char *)pom, ' ', 1000);
			//kprintf("\n");
		}
		kprintf("Boot dir: driver number: 0x%x, top partition: 0x%x, sub-partition: 0x%x\n", driver, partition, subpart);
		//kitoa(driver, pom, 16);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		//kprintf(" top partition: 0x");
		//kitoa(partition, pom, 16);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		//kprintf(" sub-partition: 0x");
		//kitoa(subpart, pom, 16);
		//kprintf(pom);
		//memset((unsigned char *)pom, ' ', 1000);
		kprintf("Arguments for Strayex: %c\n", args);
		//kprintf((char *)args);
		//kprintch('\n');
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
