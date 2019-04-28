# Budowa Strayex

W tym pliku zostało opisane, jak zbudować system Strayex z plików żródłowych.

## Potrzebne programy

Do budowy Strayex będzie potrzebne:

- Git, do pobrania plików systemu,

- GNU make, by uruchomić skrypt budujący,

- GCC Cross-Compiler, dla platformy i386-elf, w nim zawierać się będą dwa potrzebne programy: kompilator C i linker,

- NASM, do kompilacji kodu Assembly,

- GNU GRUB, narzędzia GRUBa, do użycia komendy grub-mkrescue,

- QEMU PC Emulator, do wirtualizacji systemu i testów,

## Instrukcja

Opisany tutaj sposób budowy systemu działa na dystrybucji Linux, Ubuntu. Nie był sprawdzany na systemie Windows.

1. Sklonuj repozytorium systemu na swój komputer do wybranej ścieżki:
   
   ```bash
   git clone https://github.com/StraykerPL/StrayexOS.git
   ```

2. W katalogu domowym stwórz strukturę folderów dla budowania obrazu dysku:
   
   ```bash
   mkdir iso
   cd iso
   mkdir boot
   cd boot
   mkdir grub
   cd grub
   touch grub.cfg
   ```

3. W pliku "grub.cfg" zapisz te dane:
   
   ```
   menuentry "Strayex" {
       multiboot2 /boot/skern-1.0.0.bin
   }
   ```

4. Przejdź do folderu repozytorium (w przykładzie założono, że jest on w katalogu domowym):
   
   ```bash
   cd ~/StrayexOS
   ```

5. Upewnij się, że wszystkie programy, które są wymagane do budowy są zainstalowane,

6. Jeśli wszystko jest gotowe, uruchom pełną budowę systemu:
   
   ```bash
   make
   ```
   
   Terminal powinien wyświetlić podobne dane do tych:
   
   ```
   
   Strayex Makefile informations:
   
   Kernel C files: kernel/isr_c.c kernel/main.c kernel/keyboard.c kernel/irq_c.c kernel/screen.c kernel/idt_c.c kernel/pit.c kernel/gdt_c.c kernel/klib/kstdlib.c kernel/klib/kstring.c
   Kernel ASM files: kernel/idt_asm.asm kernel/irq_asm.asm kernel/enter.asm kernel/gdt_asm.asm kernel/isr_asm.asm
   Kernel C object files: kernel/isr_c.o kernel/main.o kernel/keyboard.o kernel/irq_c.o kernel/screen.o kernel/idt_c.o kernel/pit.o kernel/gdt_c.o kernel/klib/kstdlib.o kernel/klib/kstring.o
   Kernel ASM object files: kernel/idt_asm.o kernel/irq_asm.o kernel/enter.o kernel/gdt_asm.o kernel/isr_asm.o
   
   Version of Strayex: 1.0.0
   Build architecture: i386-x86
   Kernel files directory: kernel
   GRUB build directory: /home/strayker/iso
   
   Compiling kernel Assembly file kernel/idt_asm.asm...
   Compiling kernel Assembly file kernel/irq_asm.asm...
   Compiling kernel Assembly file kernel/enter.asm...
   Compiling kernel Assembly file kernel/gdt_asm.asm...
   Compiling kernel Assembly file kernel/isr_asm.asm...
   Compiling kernel C file kernel/isr_c.c ...
   Compiling kernel C file kernel/main.c ...
   Compiling kernel C file kernel/keyboard.c ...
   Compiling kernel C file kernel/irq_c.c ...
   Compiling kernel C file kernel/screen.c ...
   Compiling kernel C file kernel/idt_c.c ...
   Compiling kernel C file kernel/pit.c ...
   Compiling kernel C file kernel/gdt_c.c ...
   Compiling kernel C file kernel/klib/kstdlib.c ...
   Compiling kernel C file kernel/klib/kstring.c ...
   Linking kernel...
   Done!
   xorriso 1.5.0 : RockRidge filesystem manipulator, libburnia project.
   
   Drive current: -outdev 'stdio:docs/strayex-i386-x86-1.0.0.iso'
   Media current: stdio file, overwriteable
   Media status : is blank
   Media summary: 0 sessions, 0 data blocks, 0 data,  116g free
   Added to ISO image: directory '/'='/tmp/grub.e99nH6'
   xorriso : UPDATE :     564 files added in 1 seconds
   Added to ISO image: directory '/'='/home/strayker/iso'
   xorriso : UPDATE :     569 files added in 1 seconds
   xorriso : NOTE : Copying to System Area: 512 bytes from file '/usr/lib/grub/i386-pc/boot_hybrid.img'
   ISO image produced: 5602 sectors
   Written to medium : 5602 sectors at LBA 0
   Writing to 'stdio:docs/strayex-i386-x86-1.0.0.iso' completed successfully.
   
   qemu-system-x86_64: warning: TCG doesn't support requested feature: CPUID.01H:ECX.vmx [bit 5]
   ```
   
   Jeśli jakakolwiek operacja zwróciła błąd, zostanie to wypisane w terminalu.

7. Jeśli budowa zakończyła się powodzeniem, powłoka powinna uruchomić emulator QEMU z systemem Strayex. Przykładowo:![qemu](https://i.pinimg.com/originals/b1/8b/dc/b18bdc767f634c2170c879fa7d2e3b63.png)
   
   W domyślnym budowaniu systemu, w obrazie płyty z systemem będzie także Strayex Legacy. Jednak jeśli budowanie odbywa się z folderem "iso" z punktu 2, w obrazie płyty znajdą się tylko te jądra, które są w podfolderze "boot" folderu "iso".

Tak przygotowany obraz płyty jest gotowy do testów!
