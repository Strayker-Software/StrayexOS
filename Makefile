# Strayex Makefile
# for version v1.0
# Copyright 2019 Daniel Strayker Nowak
# All rights reserved

# WARNING! To use this Makefile you have to install GNU make, i386-elf GCC Cross-Compiler, NASM and GNU GRUB!

# Let's start!

# Variables:

# System version:
VER:=1.0.0.0

# Kernel files' directory:
KERNEL_DIR:=kernel
# grub-mkrescue build directory:
GRUB_ISO_DIR:=~/iso/boot
# Build architecture (only for information):
ARCH:=i386-x86

# Files' lists:
KERNEL_FILES_C:=$(shell find $(KERNEL_DIR) -type f -name "*.c")
KERNEL_FILES_C_LEN:=$(words $(KERNEL_FILES_C))
KERNEL_FILES_ASM:=$(shell find $(KERNEL_DIR) -type f -name "*.asm")
OBJ_FILES_C:=$(patsubst %.c, %.o, $(KERNEL_FILES_C))
OBJ_FILES_ASM:=$(patsubst %.asm, %.o, $(KERNEL_FILES_ASM))

# make all or make - full build function, with QEMU startup!
all: info kernel iso-create clear iso-run

# make kernel - only Strayex Kernel compilation to ELF binary file:
kernel: $(KERNEL_FILES_ASM) $(KERNEL_FILES_C)
	@echo Linking kernel...
	@$$TARGET-gcc -T link.ld -o $(KERNEL_DIR)/skern-$(VER).bin -ffreestanding -O0 -nostdlib $(OBJ_FILES_ASM) $(OBJ_FILES_C) -lgcc
	@echo Done!

$(KERNEL_FILES_C): %.o %.c
	@echo Compiling kernel C file $@ ...
	@$$TARGET-gcc -c $@ -o $*.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$$PREFIX/include

$(KERNEL_FILES_ASM): %.o %.asm
	@echo Compiling kernel Assembly file $@...
	@nasm -f elf32 $@

# make info - shows info about active Makefile configuration:
info:
	@echo
	@echo Strayex Makefile informations:
	@echo
	@echo Kernel C files: $(KERNEL_FILES_C)
	@echo Kernel ASM files: $(KERNEL_FILES_ASM)
	@echo Kernel C object files: $(OBJ_FILES_C)
	@echo Kernel ASM object files: $(OBJ_FILES_ASM)
	@echo
	@echo Version of Strayex: $(VER)
	@echo Build architecture: $(ARCH)
	@echo Kernel files directory: $(KERNEL_DIR)
	@echo

# make iso-create - copies kernel's binary file to grub-mkrescue's directoryand creates GRUB ISO with it:
iso-create:
	@cp $(KERNEL_DIR)/skern-$(VER).bin ~/iso/boot/skern-$(VER).bin
	@grub-mkrescue -o ~/strayex-$(ARCH)-$(VER).iso ~/iso

# make iso-run - start QEMU with Strayex ISO file:
iso-run:
	@qemu-system-x86_64 -cdrom ~/strayex-$(ARCH)-$(VER).iso

# make clear - clears object files from working directories:
clear:
	-@$(RM) $(OBJ_FILES_C) $(OBJ_FILES_ASM)

.PHONY: all kernel info iso-create iso-run clear %.o %.c %.asm
