# How Strayex Kernel works?

As it was written in START.md file, Strayex Kernel has small requirements and doesn't need lots of data to work.
The actual version of Strayex Kernel is booted by GNU GRUB 2.02, in default ISO in repo is also Strayex Legacy.

## Strayex Start Procedure

### 1. Start of computer

After start of computer, execution BIOS instructions and finishing POST test, GRUB bootloader is started.
As the system is in ISO file, machine strats GRUB from CD drive.

### 2. Bootloader Phase

GRUB prepares the machine to work, with it's settings When it's ready to run system's kernel, it shows choose menu.
In default ISO are to kernels: Strayex Kernel and Strayex Legacy. After choosing the kernel GRUB prepares machine right with Multiboot standard (Multibooot 1 for Strayex Legacy, Multiboot 2 for Strayex Kernel).

### 3. Kernel Start

GRUB loads kernel to the memory and saves in random place Multiboot data. After giving execution to kernel, Strayex Kernel starts selfconfiguration. Execution of kernel's code starts in "enter.asm". In this file is header for GRUB, defined right with Multiboot standard. Processor don't have to execute header, this is why it's doing so called "short jump" to the right code in this file. Section ".text" from "_start" tag is doing basic things needed to run code in C: setting stack pointer and passes Multiboot data from registers on stack. After preparing data is passing execution to "main.c" file, in which kernel's main configuration is and data interpretation. Moreover "enter.asm" file has protection against unexpected code end. It is based on entering the infinitive loop under "_loop" tag, if the main code in C end execution unexpected. This protection will work only if C code will return execution, not work, by the undefined errors, C code will not execute. This loop is for preventing return to BIOS execution, give time to read data from screen and make a decision by the user. It's helphul when the user has modified C code in file and by the accident to early or involuntarily return the execution. Kernel's stack is also in "enter.asm" file in ".bss" section. It has 8KB space to grow.

In "main.c" file are to functions: "kinit" i "kmain". As you can guess, "kinit" is responsible for kernel configuration. In this version of Strayex Kernel "kmain" function is empty (comments with code are prepared). Execution of "enter.asm" file was passed to "kinit". Firs of all, function take to work Multiboot data, prepares variables for them and reads it's values from RAM. After preparing data function calls, named by me, kernel's modules' initiators. These are functions, which are executing given start instructions for respective modules, defined as devices or preparation environment for kernel's work , for example keyboard, screen or GDT and IDT. After preparation of kernel's modules, kernel can turn on interrupt controllers, "Int_on" function is used for this.

### 4. Running work mode

After the configuration kernel is ready to enter work mode, this means executing given instructions to prepare environment, right to given settings. The actual version of Strayex Kernel supports only Debug Mode, this is why turning off this mode will cause kernel's inaction after start configuration. In Debug Mode kernel prints out on screen data form GRUB's Multiboot, for example amount of system's memory, kernel's arguments or memory map. In Debug Mode are available all kernel's features but running the shell. Strayex Kernel active version doesn't support it, apart of version, besides Debug Mode will not run it netherless it will be available.

## Strayex Kernel Features

Strayex Kernel in active version don't have user space, so it's impossible to run any program, counting in CLI. However, there is option to write code inside "kmain"  kernel's function, whwre is access to all functions of kernel's standard library "klib". It's work description and functions are in "klib" folder in documentation path. Description, how to improve features of kernel by your own code are in "ADVANCED.md" file.
