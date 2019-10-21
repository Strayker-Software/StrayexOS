;  bkerndev - Bran's Kernel Development Tutorial
;  By:   Brandon F. (friesenb@gmail.com)
;  Desc: Interrupt Descriptor Table management
;
;  Notes: No warranty expressed or implied. Use at own risk.
;
;  Strayex Kernel Interrupt Descriptor Table
;  THIS IS NOT MY CODE!
;  This file was a little rewritten only, by me,
;  this is why I included above copyright header.
;  I'm not a copyright holder.

; Loads the IDT defined in "idtp" into the processor.
; This is declared in C as "extern void idt_load();":
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret
