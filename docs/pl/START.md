# Jak zacząć pracę z Strayex?

Tak jak było napisane w README.md w głównym folderze repozytorium, są cztery możliwości.
Pierwsza to pobranie gotowego pliku ISO z systemem i bootloaderem.
Druga to pobranie z repozytorium gotowego pliku jądra o nazwie "skern-(wersja).bin" i dodanie go na nośnik z bootloaderem.
Trzecia to samodzielna kompilacja jądra i umieszczenie go na nośniku z bootloaderem.
Czwarta to uruchomienie jądra poprzez parametr -kernel w QEMU.

## Uruchamianie Strayex

Tak przygotowany system jest gotowy do działania na maszynie wirtualnej, np. QEMU, VirtualBox lub VMware.
Wystarczy uruchmoić maszynę z pliku ISO i gotowe!

Warto pamiętać, że Strayex jest pełnoprawnym systemem operacyjnym i może zostać uruchomiony na prawdziwym sprzęcie, jednak odradzam tego.
Dla skonfigurowania maszyny wirtualnej poniżej jest aktualna specyfikacja minimalna dla systemu:
- procesor 32-bitowy, kompatybilny z i386,
- min. 32 MB RAM,
- monitor 80x25 na złączu VGA, zintegrowana karta graficzna,
- klawiatura na PS/2,
- dysk jest niepotrzebny w tej wersji,

Strayex jest wyposażony w jednozadaniowe mikrojądro - Strayex Kernel, które potrzebuje informacji z bootloadera, by zadziałać.
Jądro systemu jest zgodne ze [Specyfikacją Multiboot](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html) w wersji 2.0.
Bootloader zgodny z tą specyfikacją wczytuje tzw. Multiboot Information Structure do pamięci i pozostawia maszynę w zdefiniowanym stanie.

Gdy po uruchomieniu maszyny zobaczysz napis "Strayex Kernel" oraz linijkę z informacją o trybie debugowania, oznacza to, że system uruchamił się.

## Pierwsze kroki w Strayex

Aktualna dystrybucja - StrayexOS Pretorian, jest w bardzo wczesnym stanie prac i nie posiada jeszcze powłoki.
Powód jest bardzo prosty - Strayex Kernel nie jest w stanie jej obsłużyć.
Podstawowe działania, takie jak pisanie po ekranie, można wykonywać bez problemu.
By dokonywać jakiś działań w systemie, konieczna jest modyfikacja kodu jądra i ponowna kompilacja systemu.

## Co dalej?

System Strayex jest w wczesnej fazie pisania, dlatego praktycznie nie posiada funkcji.
By dowiedzieć się, co jest w planach prowadzenia projektu, przejdź do [TODO.md](https://github.com/StraykerPL/StrayexOS/blob/master/docs/TODO.md).

Teraz posiadasz podstawowe informacje o Strayex! Przejdź do kolejnego pliku [BASIC.md](https://github.com/StraykerPL/StrayexOS/blob/master/docs/pl/BASIC.md) aby kontynuować.
