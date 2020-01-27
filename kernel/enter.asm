; Strayex Kernel
; v1.1.0
; Kernel's entery point in NASM Assembly
; Copyright 2019-2020 Daniel Strayker Nowak
; All rights reserved

[BITS 32]			; Kernel loaded by Multiboot boot loader, working in 32 bit protected mode,

GLOBAL _start			; Here will jump boot loader after loading,
	jmp short _start	; so we jump to code, kernel don't have to execute Multiboot header,

; This is Multiboot header, this part must be 4 byte length (for Multiboot 1 specs) or 8 byte length (for Multiboot 2 specs),
;ALIGN 4
;Multiboot:

	; Multiboot 1:

	;MULTIBOOT_MAGIC equ 0x1BADB002
	;MULTIBOOT_PAGE equ 1 << 0
	;MULTIBOOT_MEMORY equ 1 << 0
	;MULTIBOOT_AOUT equ 1 << 16
	;MULTIBOOT_FLAGS equ MULTIBOOT_PAGE | MULTIBOOT_MEMORY | MULTIBOOT_AOUT
	;MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
	;EXTERN code, bss, end

	;dd MULTIBOOT_MAGIC
	;dd MULTIBOOT_FLAGS
	;dd MULTIBOOT_CHECKSUM

	; Multiboot 2:
	
	; Defining values:
	MAGIC equ 0xE85250D6
	ARCH equ 0x0
	LENGHT equ header_end - header_start
	CHECKSUM equ 0x100000000 - (MAGIC + ARCH + LENGHT)

; Defining header structure:
SECTION .multiboot
header_start:
	dd MAGIC
	dd ARCH
	dd LENGHT
	dd CHECKSUM

	; Tags for Multiboot bootloader:
	
	; Information request:
	ALIGN 8
request_tag_start:
	dw 1
	dw 0
	dd request_tag_end - request_tag_start
	dd 1 ; CMD line,
	dd 2 ; bootloader name,
	dd 3 ; module,
	dd 4 ; basic memory amount,
	dd 5 ; boot partition's informations,
	dd 6 ; memory map,
request_tag_end:

	; Module align to page size requset:
	ALIGN 8
module_align_start:
	dw 6
	dw 0
	dd module_align_end - module_align_start
module_align_end:

	ALIGN 8
	; End of tags, "NULL tag":
null_start:
	dw 0 ; Type
	dw 0 ; Flags
	dd 8 ; Size
null_end:
	
header_end: ; End of Multiboot header!

SECTION .text
_start:
	mov esp, stack		; Sets stack space in register,
	
	push $0				; Reset EFLAGS,
	popf
	
	push ebx			; Push on stack address to MBI
	push eax			; and MB magic number,

	EXTERN kinit		; kinit function: kernel initialisation process, in main.c,
	call kinit			; jump to the kinit and call kmain there,

_loop:					; if C functions will unexpectly return, loop for ever, 
	jmp _loop
	
SECTION .bss
resb 16384			; Stack space, 16KB,
stack:

