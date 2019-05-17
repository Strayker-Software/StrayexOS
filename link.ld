/*
	Strayex Linkscript
	Copyright (a) 2019 Daniel Strayker Nowak
	All rights reserved
	
	This file specifies, how should look like end product - binary file.
	This script is for i386-elf-ld and objects files.
/*

/* Specify binary format: */
OUTPUT_FORMAT("elf32-i386")
/* Point execution to label in "enter.asm" */
ENTRY(_start)
/* Specifies file's structure: */
SECTIONS
{
	/* Map kernel in start of 1 MB, */
	. = 1M;
	
	/* Start of Kernel tag: */
	_sok = .;
	
	/* Block for Multiboot header: */
	.mb BLOCK(8K) : ALIGN(8K)
	{
		*(.multiboot)
	}
	
	/* Block for code: */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text)
	}

	/* Block for initialised data: */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Block for stack and other data: */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
	
	/* End of Kernel tag: */
	_eok = .;
}
