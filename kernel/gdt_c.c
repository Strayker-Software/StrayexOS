/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Global Descriptor Table management
*
*  Notes: No warranty expressed or implied. Use at own risk.

   Strayex Kernel Global Descriptor Table
   THIS IS NOT MY CODE!
   This file was a little rewritten only, by me,
   this is why I included above copyright header.
   I'm not a copyright holder.
*/

#include "klib/kdt.h"

// GDT entry:
struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

// GDT special pointer:
struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

// GDT and special pointer variables:
struct gdt_entry gdt[3];
struct gdt_ptr gp;

// Assembly shortcut for setting up GDT into memory and processor:
extern void gdt_flush();

// Sets entry in GDT:
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
	// Entry base address:
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	// Entry limits:
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	// Entry granularity:
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

// GDT initialisation:
int gdt_init()
{
	/* Setup the GDT pointer and limit */
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = (unsigned int)&gdt;

	/* Our NULL descriptor */
	gdt_set_gate(0, 0, 0, 0, 0);

	/* The second entry is our Code Segment. The base address
	*  is 0, the limit is 4GBytes, it uses 4KByte granularity,
	*  uses 32-bit opcodes, and is a Code Segment descriptor.
	*  Please check the table above in the tutorial in order
	*  to see exactly what each value means */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* The third entry is our Data Segment. It's EXACTLY the
	*  same as our code segment, but the descriptor type in
	*  this entry's access byte says it's a Data Segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	/* Flush out the old GDT and install the new changes! */
	gdt_flush();

	return 0;
}
