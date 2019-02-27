; Strayex Kernel
; v1.0
; Kernel's entery point in NASM Assembly

; TODO: Dodać nagłówek GPL!

[BITS 32]			; Kernel loaded by GNU GRUB with Multiboot, working in 32 bit protected mode,

GLOBAL _start			; Here will jump GRUB after loading,
	jmp short _start	; so we jump to code, kernel don't have to read Multiboot header,

; This is Multiboot header, this part must be 4 byte length (for Multiboot 1 specs) or 8 byte length (for Multiboot 2 specs),
ALIGN 4
Multiboot:

	; Multiboot 1:

	MULTIBOOT_MAGIC equ 0x1BADB002
	MULTIBOOT_PAGE equ 1 << 0
	MULTIBOOT_MEMORY equ 1 << 0
	MULTIBOOT_AOUT equ 1 << 16
	MULTIBOOT_FLAGS equ MULTIBOOT_PAGE | MULTIBOOT_MEMORY | MULTIBOOT_AOUT
	MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
	EXTERN code, bss, end

	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_FLAGS
	dd MULTIBOOT_CHECKSUM

	; Multiboot 2, not working, do not use!

;ALIGN 8
;Multiboot:
	;MULTIBOOT_MAGIC equ 0xE85250D6
	;MULTIBOOT_ARCH equ 0x0
	;MULTIBOOT_HEADER_LENGTH equ _start - Multiboot
	;MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_ARCH + MULTIBOOT_HEADER_LENGTH)
	;MULTIBOOT_MODULE equ 3
	;MULTIBOOT_BASIC_MEMINFO equ 4
	;MULTIBOOT_BOOT_LOADER_NAME equ 2
	;MULTIBOOT_MMAP equ 6
	;EXTERN code, bss, end

	;dd MULTIBOOT_MAGIC
	;dd MULTIBOOT_ARCH
	;dd MULTIBOOT_HEADER_LENGTH
	;dd MULTIBOOT_CHECKSUM
	;dd MULTIBOOT_MODULE
	;dd MULTIBOOT_BASIC_MEMINFO
	;dd MULTIBOOT_BOOT_LOADER_NAME
	;dd MULTIBOOT_MMAP

; End of Multiboot header,
; here is memory defining for linker,

	dd Multiboot
	dd code
	dd bss
	dd end
	dd _start

_start:
	mov esp, stack		; Sets stack space in register,

	EXTERN kinit		; kinit function: kernel initialisation process, in main.c,
	call kinit		; jump to the kinit and call kmain there,

SECTION .bss
resb 8192			; Stack space, 8KiB,
stack:

