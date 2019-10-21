;  bkerndev - Bran's Kernel Development Tutorial
;  By:   Brandon F. (friesenb@gmail.com)
;  Desc: Global Descriptor Table management
;
;  Notes: No warranty expressed or implied. Use at own risk.
;
;  Strayex Kernel Global Descriptor Table
;  THIS IS NOT MY CODE!
;  This file was a little rewritten only, by me,
;  this is why I included above copyright header.
;  I'm not a copyright holder.

global gdt_flush			; Allows the C code to link to this,
extern gp					; Says that "gp" is in another file,
gdt_flush:
    lgdt [gp]				; Load the GDT with our "gp" which is a special pointer,
    mov ax, 0x10		; 0x10 is the offset in the GDT to our data segment,
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2	; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret						; Returns back to the C code!
