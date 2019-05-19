# Kernel Memory Header

Nagłówek "kmem.h" to plik łączący funkcje menadżera pamięci jądra. W tym pliku są łącza do dwuch podstawowych funkcji pamięci - "kmalloc" i "kfree".

Menadżer pamięci opiera się na tzw. "Waterflow mark". Rezerwuje pamięć, od najniższego adresu do najwyższego, zwalnia odwrotnie.

## Definicje

Brak.

## Funkcje

- bool mem_init(unsigned int ram_in_kb)

Ustawia wartość, ile pamięci ma menadżer do dyspozycji.

Argumenty: dodatnia liczba, wskazująca ilość RAMu w komputerze,

Zwraca: zawsze prawdę,

- void *kmalloc(int size)

Funkcja rezerwuje daną ilość bajtów w pamięci.

Argumenty: liczba całkowita, ilość bajtów do zarezerwowania,

Zwraca: adres do zarezerwowanej pamięci,

- void kfree(void *addr)

Funkcja zwalnia przesrzeń danego adresu.

Argumenty: adres do przestrzeni do zwolnienia,

Zwraca: brak,
