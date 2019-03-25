# Strayex Makefile
# for version v1.0
# Copyright 2019 Daniel Strayker Nowak
# All rights reserved

# WARNING! To use this Makefile you have to install GNU make, i386-elf GCC Cross-Compiler, NASM and GNU GRUB!

# Let's start!
# This Makefile give you opportunity of various operations with Strayex source files.
# Each make sub-command make for you part of the job, you can specify, which sub-command you want to perform by typing "make [sub-command]".
# Here is the list:
# - make - full build with starting QEMU debbuging,
# - make info - show Makefile's settings and list of source files,
# - make kernel - only kernel compilation and linking,
# - make iso-create - push binary file of kernel to GRUB bootable ISO,
# - make iso_run - boot QEMU x86_64 form GRUB bootable ISO,
# Futuremore, over each sub-command is it's description for your convenience.

# Variables
# If you want to make tests, or personalise build process, change this values.

# System version:
VER:=1.0.0.0

# Kernel files' directory (where are files to compile):
KERNEL_DIR:=kernel
# grub-mkrescue build directory (where to push binary kernel):
GRUB_ISO_DIR:=~/iso
# Build architecture (for naming system):
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
	@$$TARGET-gcc -T link.ld -o $(KERNEL_DIR)/skern-$(VER).bin -ffreestanding -nostdlib $(OBJ_FILES_ASM) $(OBJ_FILES_C) -lgcc
	@echo Done!

$(KERNEL_FILES_C): %.o %.c
	@echo Compiling kernel C file $@ ...
	@$$TARGET-gcc -c $@ -o $*.o -std=gnu99 -ffreestanding -Wall -Wextra -I$$PREFIX/include

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
	@echo GRUB build directory: $(GRUB_ISO_DIR)
	@echo

# make iso-create - copies kernel's binary file to grub-mkrescue's directoryand creates GRUB ISO with it:
iso-create:
	@cp $(KERNEL_DIR)/skern-$(VER).bin $(GRUB_ISO_DIR)/boot/skern-$(VER).bin
	@grub-mkrescue -o docs/strayex-$(ARCH)-$(VER).iso $(GRUB_ISO_DIR)

# make iso-run - start QEMU with Strayex ISO file:
iso-run:
	@qemu-system-x86_64 -D serial.log -no-reboot -no-shutdown -m 128M -cdrom docs/strayex-$(ARCH)-$(VER).iso

# make clear - clears object files from working directories:
clear:
	-@$(RM) $(OBJ_FILES_C) $(OBJ_FILES_ASM)

.PHONY: all kernel info iso-create iso-run clear %.o %.c %.asm
