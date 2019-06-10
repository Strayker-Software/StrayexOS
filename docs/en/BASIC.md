# Strayex basic informations

## Strayex architecture

StrayexOS works on monotasking microkernel - Strayex Kernel. It was written in C and NASM Assembly.
Files are in "kernel" directory in repository.

It was build from three parts:

- in folder "kernel/klib" is custom C library,
- .c kernel files,
- .asm kernel files,

Makefile converts all files to objects in ones - ASM, C and klib.

### Strayex Kernel

Kernel works on Intel i386 architecture. It's compiled to ELF file and supports Multiboot Specification.
Main kernel jobs are: mapping descriptors tables (GDT, IDT), interrupt services (ISR, IRQ) and computer's chips service (PS/2, PIT).

### Strayex Kernel Library

Is located in "kernel/klib". It contains necessary functions for kernel, like kprintf and koutportb.

### Drivers

Strayex have drivers to serve to basic periphery: VGA monitor and PS/2 keyboard.
Drivers' files are called "screen.c" and "keyboard.c", respectively.

## Running

After computer's power on with Strayex, GRUB starts up and shows up a list with available systems to run.
If you have clear Strayex ISO, on list will exist only one kernel. When you choose it, system will start to load.
In depend of kernel's settings, system can show up informations about computer from bootloader while starting.
After showing data kernel will jump to main function and will execute instructions written there.

# System's memory management

![mem](https://i.pinimg.com/originals/10/01/93/1001930758806f4a84117e7da1fabbd6.jpg)

The above map shows how memory is managed. It's modification is made by memory manager in setup of two functions: "kmalloc" and "kfree", with variables with additional data. Library that contains these functions is "kmem" in setup of two files: "mem.c" and "kmem.h" in appropriate folders. In 1 Megabyte mark is beggining of Strayex Kernel, in 2 Megabytes mark - Strayex Shell.
