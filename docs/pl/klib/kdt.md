# Kernel Descriptor Table Header

Nagłówek "kdt.h" to biblioteka zawierająca łącza do funkcji związanych z tablicami deskryptorów.

UWAGA! Używanie tych funkcji przy zwykłych operacjach niezwiązanych z wczytywaniem Strayex Kernel może być niebezpieczne.

Podpowiedź: każda funkcja zaczynająca się na "k" to funkcja z biblioteki jądra.

## Definicje

struct regs

Struktura, która przechowuje wygląd i dane rejestrów procesora po wykonaniu ISR.

## Funkcje

"kdt.h" łączy funkcje z wielu plików, mi.: "gdt_c.c" i "idt_c.c".

- int gdt_init()

Funkcja przygotowuje i instaluje w pamięci GDT (General Descriptor Table).

Argumenty: brak,

Zwraca: zawsze 0,

- void idt_init()

Funkcja przygotowuje i instaluje w pamięci IDT (Interrupt Descriptor Table).

Argumenty: brak,

Zwraca: brak,

- void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)

Funkcja ustawia dane wejście w IDT z podanymi danymi.

Argumenty: num - indeks w IDT, base - adres ISR, sel - segment lub "selector", flags - ustawienia dla danej bramy,

Zwraca: brak,

- void isrs_init()

Funkcja mapuje pierwsze 32 ISR do pierwszych 32 IRQ. Jest ona statyczna i niezbędna do zremapowania IRQ w dalszym etapie.

Argumenty: brak,

Zwraca: brak,

- void irq_install_handler(int irq, void (*handler)(struct regs *r))

Funkcja instaluje w podanym IRQ daną funkcję.

Argumenty: irq - numer IRQ, void (*handler)(struct regs *r) - funkcja, jaką zmapować do danego IRQ,

Zwraca: brak,

- void irq_init()

Funkcja remapuje kontrolery przerwań i instaluje obsługę przerwań dla trybu chronionego.

Argumenty: brak,

Zwraca: brak,
