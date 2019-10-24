# Jak działa Strayex Kernel?

Jak zostało podane w pliku START.md, Strayex Kernel ma małe wymagania i nie potrzebuje dużo danych do działania.
Aktualną wersję Strayex Kernel boot'uje GNU GRUB 2.02, w domyślnym ISO z repozytorium jest również Strayex Legacy.

## Procedura startu Strayex

### 1. Start komputera

Po uruchomieniu komputera, wykonaniu instrukcji BIOSu i zakończeniu testu POST, następuje uruchomienie bootloader'a GRUB.
Jako że system znajduje się w pliku ISO, maszyna uruchamia GRUBa z stacji CD.

### 2. Faza Bootloader'a

GRUB przygotowuje maszynę do działania, zgodnie z swoimi ustawieniami. Gdy jest gotowy uruchomić jądro systemu, pokazuje menu wyboru.
W domyślnym ISO są dwa jądra do wyboru: Strayex Kernel i Strayex Legacy. Po wybraniu jądra GRUB przygotuje maszynę zgodnie z standardem Multiboot (Multibooot 1 dla Strayex Legacy, Multiboot 2 dla Strayex Kernel).

### 3. Start jądra

GRUB załadowuje jądro do pamięci i zapisuje w losowo wybranym miejscu dane Multiboot. Po przekazaniu wykonywania do jądra, Strayex Kernel rozpoczyna konfigurację.

