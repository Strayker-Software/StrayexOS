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
Aufgaben des Hauptkernels sind: Zuordnung von Deskriptortabellen (GDT, IDT), Dienste unterbrechen (ISR, IRQ) und Computer Chips Service (PS/2), PIT).

### Strayex Kernel Bibilotek 
Sie befindet sich in "kernel/klib". Sie enthält notwendige Funktionen für den Kernel, wie z.B kprintf und koutprotb.

### Treiber

Strayex hat Treiber für die Standart Peripherie-Geräte: VGA Monitor oder PS/2 Tastatur 
Die Treiber Dateien heißen "screen.c" beziehungsweise "keyboard.c"

## Betrieb 

Nachdem der Computer angeschlatet ist, startet GRUB und zeigt eine Liste von verfügbaren Betriebssystemen an.
Wenn du eine bestimmte Strayex ISO hast wird in der Liste nur ein Kernel erscheinen. Wenn du diesen auswählst, wird das System anfangen zu laden.
Abhängig von den Einstellugen des Kernels, kann das Betriebssystem, während des Hochfahrens Informationen über den Computer vom Bootloder anzeigen. Nach dem Informationen des Kernels angezeigt wurden, springt der Kernel zur Main Funktuion und wird die Anweisungen die dort hineingeschrieben wurden, ausführen.

# System Speicher Verwaltung

![mem](https://i.pinimg.com/originals/10/01/93/1001930758806f4a84117e7da1fabbd6.jpg)

Dieses Bild zeigt wie der Speicher verwaltet wird. Seine Änderungen werden vom Speicher Verwalter mit hilfe von zwei Funktionen vorgenommen: "kmalloc" und "kfree", mit Variablen und zusätzlichen Daten. Die Bibilotehk welche diese Funktionen enthält nennt sich "kmen" bestehend aus den beiden Dateien: "mem.c" und "kmen.h" in den jeweiligen Ordnern. 
Ab der 1 Megabyte Marke beginnt der Strayex Kernel, ab 2 Megabyte die Strayex Shell.
