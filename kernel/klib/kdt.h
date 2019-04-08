/*
 Strayex Kernel C Library "klib"
 v1.0.0
 Kernel Descriptor Tables Header
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _KDT_
#define _KDT_

// How stack look like after ISR:
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

extern int gdt_init(); // in gdt_c.c
extern void idt_init(); // in idt_c.c
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags); // in idt_c.c
extern void isrs_init(); // in isr_c.c
extern void irq_install_handler(int irq, void (*handler)(struct regs *r)); // in irq_c.c
extern void irq_init(); // in irq_c.c

#endif
