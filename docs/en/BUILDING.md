# Building Strayex

In this file was described, how to build Strayex system from source files.

## Necessary programs

To build Strayex will be necessary having:

- Git, to download system files,

- GNU make, to run build script,

- GCC Cross-Compiler, for i386-elf platform, there will be to necessary programs in it: C compiler and linker,

- NASM, to compile Assembly code,

- GNU GRUB, GRUB utilities, to use grub-mkrescue command,

- QEMU PC Emulator, to virtualize and test system,

## Instruction

The way of building system described here works on Linux distribution, Ubuntu. It wasn't tested on Windows system.

1. Clone system repository on your computer to choosen path:
   
   ```bash
   git clone https://github.com/StraykerPL/StrayexOS.git
   ```

2. In home catalog create folder tree for building of disk image:
   
   ```bash
   mkdir iso
   cd iso
   mkdir boot
   cd boot
   mkdir grub
   cd grub
   touch grub.cfg
   ```

3. In file"grub.cfg" write given data:
   
   ```
   menuentry "Strayex" {
       multiboot2 /boot/skern-1.0.0.bin
   }
   ```

4. Enter to repository folder (in this example assumed, that repository is in home catalog):
   
   ```bash
   cd ~/StrayexOS
   ```

5. Make sure, that all programs needed to build up, are installed,

6. If everything is ready, run full build of system:
   
   ```bash
   make
   ```
   
   Terminal should show simmilar data to that:
   
   ```
   
   Strayex Makefile informations:
   
   Kernel C files: kernel/isr_c.c kernel/main.c kernel/keyboard.c kernel/irq_c.c kernel/screen.c kernel/idt_c.c kernel/pit.c kernel/gdt_c.c kernel/klib/kstdlib.c kernel/klib/kstring.c
   Kernel ASM files: kernel/idt_asm.asm kernel/irq_asm.asm kernel/enter.asm kernel/gdt_asm.asm kernel/isr_asm.asm
   Kernel C object files: kernel/isr_c.o kernel/main.o kernel/keyboard.o kernel/irq_c.o kernel/screen.o kernel/idt_c.o kernel/pit.o kernel/gdt_c.o kernel/klib/kstdlib.o kernel/klib/kstring.o
   Kernel ASM object files: kernel/idt_asm.o kernel/irq_asm.o kernel/enter.o kernel/gdt_asm.o kernel/isr_asm.o
   
   Version of Strayex: 1.0.0
   Build architecture: i386-x86
   Kernel files directory: kernel
   GRUB build directory: /home/strayker/iso
   
   Compiling kernel Assembly file kernel/idt_asm.asm...
   Compiling kernel Assembly file kernel/irq_asm.asm...
   Compiling kernel Assembly file kernel/enter.asm...
   Compiling kernel Assembly file kernel/gdt_asm.asm...
   Compiling kernel Assembly file kernel/isr_asm.asm...
   Compiling kernel C file kernel/isr_c.c ...
   Compiling kernel C file kernel/main.c ...
   Compiling kernel C file kernel/keyboard.c ...
   Compiling kernel C file kernel/irq_c.c ...
   Compiling kernel C file kernel/screen.c ...
   Compiling kernel C file kernel/idt_c.c ...
   Compiling kernel C file kernel/pit.c ...
   Compiling kernel C file kernel/gdt_c.c ...
   Compiling kernel C file kernel/klib/kstdlib.c ...
   Compiling kernel C file kernel/klib/kstring.c ...
   Linking kernel...
   Done!
   xorriso 1.5.0 : RockRidge filesystem manipulator, libburnia project.
   
   Drive current: -outdev 'stdio:docs/strayex-i386-x86-1.0.0.iso'
   Media current: stdio file, overwriteable
   Media status : is blank
   Media summary: 0 sessions, 0 data blocks, 0 data,  116g free
   Added to ISO image: directory '/'='/tmp/grub.e99nH6'
   xorriso : UPDATE :     564 files added in 1 seconds
   Added to ISO image: directory '/'='/home/strayker/iso'
   xorriso : UPDATE :     569 files added in 1 seconds
   xorriso : NOTE : Copying to System Area: 512 bytes from file '/usr/lib/grub/i386-pc/boot_hybrid.img'
   ISO image produced: 5602 sectors
   Written to medium : 5602 sectors at LBA 0
   Writing to 'stdio:docs/strayex-i386-x86-1.0.0.iso' completed successfully.
   
   qemu-system-x86_64: warning: TCG doesn't support requested feature: CPUID.01H:ECX.vmx [bit 5]
   ```
   
   If any operation returned error, it will be written in terminal.

7. If system build ended successful, shell should run QEMU emulator with Strayex system. For example:![qemu](https://i.pinimg.com/originals/b1/8b/dc/b18bdc767f634c2170c879fa7d2e3b63.png)
   
   In default system build, Strayex Legacy will be on system disk image. However, if build is performed with "iso" folder from point 2, in disk image will be these kernels, whitch are in sybfolder "boot" of folder "iso".

In that way prepared disk image is ready for tests!
