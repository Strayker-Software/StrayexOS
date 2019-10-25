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

GRUB załadowuje jądro do pamięci i zapisuje w losowo wybranym miejscu dane Multiboot. Po przekazaniu wykonywania do jądra, Strayex Kernel rozpoczyna konfigurację. Wykonywanie kodu jądra zaczyna się w pliku "enter.asm". W tym pliku znajduje się nagłówek dla GRUBa, zdefiniowany zgodnie ze standardem Multiboot. Procesor nie musi wykonywać nagłówka, dlatego procesor wykonuje tzw. "krótki skok" do prawidłowego kodu w tym pliku. Sekcja ".text" od tagu "_start" wykonuje podstawowe czynności potrzebne do uruchomienia kodu w C: ustawia wskaźnik stosu i przekazuje dane Multiboot z rejestrów na stos. Po przygotowaniu danych przekazuje wykonanie do pliku "main.c", w którym dokonuje się konfiguracja głównych funkcji jądra i interpretacja danych. Ponad to plik "enter.asm" posiada zabezpieczenie przeciwko nieoczekiwanym zakończeniem kodu. Polega na wejściu w nieskończoną pętlę o tagu "_loop" w pliku, gdyby główny kod w C nagle zakończył wykonywanie. To zabezpieczenie zadziała tylko wtedy, gdy kod w C zwróci wykonywanie, czyli nie zadziała, gdy przez błędy bliżej nieokreślone, kod w C się nie wykona. Ta pętla ma na celu zapobiec powrotu do wykonywania BIOSu, dać czas na odczytanie danych z ekranu i podjęcie decyzji przez urzytkownika. Przydaje się, gdy urzytkownik zmodyfikował kod w C i przez przypadek za wcześnie lub nieumyślnie zwrócił wykonywanie. Stos jądra także znajduje się w pliku "enter.asm" w sekcji ".bss". Ma on 8KB przestrzeni do rośnięcia.

W pliku "main.c" są dwie główne funkcje: "kinit" i "kmain". Jak łatwo się domyśleć, "kinit" odpowiada za konfigurację jądra. W tej wersji Strayex Kernel funkcja "kmain" jest pusta (przygotowane są komentarze z kodem). Wykonywanie z pliku "enter.asm" zostało przekazane do funkcji "kinit". Najpierw funkcja zajmuje się danymi Multiboot, przygotowuje dla nich zmienne i  odczytuje je z pamięci RAM. Po przygotowaniu danych funkcja wywołuje, nazwane przeze mnie, inicjatory modułów jądra. To funkcje, które wykonują dane instrukcje startowe dla odpowiednich dla siebie modułów, zdefiniowanych  jako dane urządzenia lub przygotowanie środowiska do pracy jądra, na przykład klawiatury, ekranu czy GDT i IDT. Po przygotowaniu modułów jądro może włączyć kontroler przerwań, służy do tego funkcja "Int_on".

### 4. Uruchamianie trybu pracy

Po konfiguracji jądro jest gotowe wejść w tryb pracy, czyli wykonać odpowiednie czynności przygotowywujące środowisko, wedle danych ustawień. Aktualna wersja Strayex Kernel obsługuje tylko tryb debuggowania (Debug Mode), dlatego wyłączenie tego trybu spowoduje bezczynność jądra po konfiguracji startowej. W trybie debuggowania jądro wypisuje na ekranie dane pozyskane z Multiboot GRUBa, na przykład ilość pamięci systemowej, argumenty dla jądra czy mapę pamięci. W trybie debuggowania są dostępne wszystkie funkcjonalności jądra poza uruchomieniem powłoki. Aktualna wersja Strayex Kernel jej nie obsługuje, niezależnie od trybu, jendak tryb debuggowania nie będzie jej uruchamiał nawet wtedy gdy będzie dostępna.

## Funkcje Strayex Kernel

Strayex Kernel w aktualnej wersji nie posiada przestrzeni urzytkownika, czyli nie może uruchomić żadnego programu, w tym powłoki komend. Jednak jest możliwe napisanie kodu bezpośrednio w funkcji "kmain" jądra, gdzie ma się dostęp do wszystkich funkcji biblioteki standardowej jądra "klib". Jej opis działania i funkcje znajdują się w dokumentacji projektu w folderze "klib". Opis, jak rozwinąć możliwości jądra własnym kodem znajduje się w pliku "ADVANCED.md".


