# Strayex Grundlegende Informationen

## Strayex Architektur 

StrayexOS arbeitet mit einem Monotasking Mikrokernel dem Strayex Kernel. Er wurde in C und NASM Assembly geschrieben.
Dateien sind im "Kernel" Verzeichnis im Repository 

Es wurde aus drei Teilen gebaut:

- im Ordner "kernel/klib" ist eine benutzerdefinierte C Bibilothek,
- .c Kernel Dateien
- .asm Kernel Dateien,

Das Makefile konvertiert alle Dateien zu Objekte in einem - ASM, C und klib.

### Strayex kernel 
Der Kernel arbeitet auf der Intel i386 Architektur. Es ist in ELF kompiliert und unterstüzt Multiboot Spezifikationen.
Aufgaben des Hauptkernels sind: 
