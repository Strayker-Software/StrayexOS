# Podstwowe informacje o Strayex

## Budowa Strayex

StrayexOS działa na jednozadaniowym mikro jądrze - Strayex Kernel. Napisane zostało w C i NASM Assembly.
Pliki znajdują się w folderze "kernel" repozytorium.

Składa się z trzech części:

- w folderze "kernel/klib" jest niestandardowa biblioteka C jądra,
- pliki .c jądra,
- pliki .asm jądra,

Plik Makefile przetwarza na obiekty pliki jądra wszystkie razem - ASM, C i klib.

### Strayex Kernel

Jądro działa na architekturze Intel i386. Jest w formacje ELF oraz wspiera specyfikację Multiboot.
Do głównych zadań jądra należy zmapowanie tablic deskryptorów (GDT, IDT), obsługi przerwań (ISR, IRQ) oraz obsługi czipów komputera (PS/2, PIT).

### Strayex Kernel Library

Znajduje się w folderze "kernel/klib". Zawiera funkcje potrzebne do działania jądra, takie jak kprintf i koutportb.

### Sterowniki

Strayex ma sterowniki do obsługi dwóch podstawowych peryferiów: monitora na VGA i klawiatury PS/2.
Pliki sterowników nazywają się "screen.c" oraz "keyboard.c".

## Uruchamianie

Po włączeniu komputera z systemem Strayex, uruchamia się GRUB i wyświetla się lista z dostępnymi systemami do uruchomienia.
Jeśli posiadasz czyste ISO Strayex, na liście będzie tylko jedno jądro. Gdy je wybierzesz, system zacznie się ładować.
W zależności od ustawień jądra, system może podczas ładowania wyświetlić dane o komputerze z bootloadera.
Po wyświetleniu danych jądro wskoczy do głównej funkcji i będzie wykonywać zawarte w niej instrukcje.

# Zarządzanie pamięcią w systemie

![mem](https://i.pinimg.com/originals/10/01/93/1001930758806f4a84117e7da1fabbd6.jpg)

Powyższa mapa pamięci obrazuje, jak zagospodarowana jest pamięć operacyjna podczas pracy Strayex. Jej edycją zajmuje się menadżer pamięci w postaci dwóch funkcji: "kmalloc" i "kfree", z zmiennymi na pomocnicze dane. Biblioteka, która zawiera te funkcje to "kmem" w postaci dwóch plików "mem.c" i "kmem.h" w odpowiednich folderach kodu jądra. W znaczniku 1 megabajta znajduje się początek jądra Strayex Kernel, w znaczniku 2 megabajtów - Strayex Shell.
