# Kernel Descriptor Table Header

"kdt.h" header is library to connect functions to operate on descriptors tables.

WATCH OUT! Using this functions to another things than loading Strayex Kernel can be dangerous!

Hint: every function with name starting with "k" is function from klib.

## Definitions

struct regs

Structure that holds look and data of processor's registers after ISR execution.

## Functions

"kdt.h" connects functions from many files, for examples: "gdt_c.c" and "idt_c.c".

- int gdt_init()

Function prepares and installs into memory GDT (General Descriptor Table).

Arguments: none,

Returns: always 0,

- void idt_init()

Function prepares and installs into memory IDT (Interrupt Descriptor Table).

Arguments: none,

Returns: none,

- void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)

Function sets given entry in IDT with given data.

Arguments: num - IDT index, base - ISR address, sel - segment or "selector", flags - settings for given gate,

Returns: none,

- void isrs_init()

Function maps first 32 ISR to first 32 IRQ. It's essential and must-be to remap IRQs in next stage.

Arguments: none,

Returns: none,

- void irq_install_handler(int irq, void (*handler)(struct regs *r))

Function installs given function in given IRQ.

Arguments: irq - IRQ number, void (*handler)(struct regs *r) - function which will be installed to IRQ,

Returns: none,

- void irq_init()

Function remaps interrupt controllers and installs interrupt service for protected mode.

Arguments: none,

Returns: none,
