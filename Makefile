# Strayex Makefile
# for version v1.1.0
# Copyright 2019-2020 Daniel Strayker Nowak
# All rights reserved

# WARNING! To use this Makefile you have to install GNU make, i386-elf GCC Cross-Compiler, NASM and GNU GRUB!

# Let's start!
# This Makefile give you opportunity of various operations with Strayex source files.
# Each make sub-command make for you part of the job, you can specify, which sub-command you want to perform by typing "make [sub-command]".
# Here is the list:
# - make - full build, default is normal build mode with starting QEMU,
# - make info - show Makefile's settings and list of source files,
# - make kernel - only kernel compilation and linking,
# - make iso-create - push binary file of kernel to GRUB bootable ISO,
# - make iso-run-qemu - boot QEMU x86_64 from GRUB bootable ISO,
# - make iso-run-bochs - boot Bochs from GRUB bootable ISO,
# - make check-toolset - checks, if all additional software is provided in host OS,
# Futuremore, over each sub-command is provided it's description for your convenience.

#Use Bash for this script:
SHELL:=/bin/bash

# Variables
# If you want to make tests, or personalise build process, change this values.

# System version:
VER:=1.1.0

# Kernel files' directory (where are files to compile):
KERNEL_DIR:=kernel
# grub-mkrescue build directory (where to push binary kernel).
# You have to create this directory and add GRUB config file.
# See Strayex Docs for more instructions.
GRUB_ISO_DIR:=iso
# Build architecture (for naming system):
ARCH:=x86
# Path to Cross-Compiler:
CROSS:=/home/strayker/cross

# Files' lists:
KERNEL_FILES_C:=$(shell find $(KERNEL_DIR) -type f -name "*.c")
KERNEL_FILES_ASM:=$(shell find $(KERNEL_DIR) -type f -name "*.asm")
OBJ_FILES_C:=$(patsubst %.c, %.o, $(KERNEL_FILES_C))
OBJ_FILES_ASM:=$(patsubst %.asm, %.o, $(KERNEL_FILES_ASM))

# make all or make - full build function, with QEMU startup!
all: info kernel iso-create clear iso-run-qemu

# make check-toolset - checks, if all additional software is provided in host OS:
check-toolset:
	@echo
	@echo Checking i386-elf GCC Cross-Compiler...
	@echo
	@i386-elf-gcc --version
	@if [ $?="0" ]; then echo "OK!"; else echo "Error here! Check your compiler!"; fi
	@echo
	@echo Checking NASM Assembly...
	@echo
	@nasm --version
	@if [ $?="0" ]; then echo "OK!"; else echo "Error here! Check NASM!"; fi
	@echo
	@echo Checking GRUB utils for grub-mkrescue command...
	@echo
	@grub-mkrescue --version
	@if [ $?="0" ]; then echo "OK!"; else echo "Error here! Check GRUB utils!"; fi
	@echo
	@echo Control completed! Check this output for errors.

# make kernel - only Strayex Kernel compilation to ELF binary file:
kernel: $(KERNEL_FILES_ASM) $(KERNEL_FILES_C)
	@echo Linking kernel...
	@i386-elf-gcc -T link.ld -o $(KERNEL_DIR)/skern-$(VER).bin -ffreestanding -fstack-protector-all -nostdlib $(OBJ_FILES_ASM) $(OBJ_FILES_C) -lgcc
	@echo Done!

$(KERNEL_FILES_C): %.o %.c
	@echo Compiling kernel C file $@ ...
	@i386-elf-gcc -c $@ -o $*.o -std=gnu99 -ffreestanding -Wall -Wextra -I$(CROSS)/include

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
	@echo Cross-Compiler directory: $(CROSS)
	@echo

# make iso-create - copies kernel's binary file to grub-mkrescue's directory and creates GRUB ISO with it:
iso-create:
	@cp $(KERNEL_DIR)/skern-$(VER).bin $(GRUB_ISO_DIR)/boot/skern-$(VER).bin
	@grub-mkrescue -o docs/strayex-$(ARCH)-$(VER).iso $(GRUB_ISO_DIR)

# make iso-run - start QEMU with Strayex ISO file:
iso-run-qemu:
	@qemu-system-x86_64 -serial file:serial.log -m 128M -cdrom docs/strayex-$(ARCH)-$(VER).iso

# make iso-run-qemu - start QEMU with Strayex ISO file, but QEMU don't show up GUI, for GitHub CI:
is-run-qemu-nographic:
	@qemu-system-x86_64 -nographic -serial file:serial.log -m 128M -cdrom docs/strayex-$(ARCH)-$(VER).iso
	
# make iso-run-bochs - start Bochs with Strayex ISO file, this command uses config file:
iso-run-bochs:
	@bochs -f docs/.bochsrc -q

# make clear - clears object files from working directories:
clear:
	-@$(RM) $(OBJ_FILES_C) $(OBJ_FILES_ASM)

.PHONY: all check-toolset kernel info iso-create iso-run-qemu is-run-qemu-nographic iso-run-bochs clear %.o %.c %.asm
