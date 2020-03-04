# Wie fange ich an mit Strayex zu arbeiten?

Wie es in README.md geschrieben steht, gibt es drei Wege.
Erstens, Lade die vorgefertigte ISO Datei mit Kernel und Bootloader herunter
Zweitens, Lade die vorgefertigte Binärdatei des Kernels mit dem Namen "skern-(wersja).bin" herunter und füge sie enem Gerät mit installierten Bootloader hinzu
Drittens, Baue den Kernel selbst und füge ihn einem Gerät mit installierten Bootloader hinzu.
Viertens, führe den Kernel im QEMU mit dem Parameter -kernel aus

## Strayex ausführen

Wählst du einer dieser Möglichkeiten aus ist das Betriebssystem nun bereit auf Virtuellen Maschinen wie QEMU, VirtualBox or VMWare zu laufen. Du brauchst einfach nur eine VM mit der ISO zu starten und schon bist du fertig!

Es ist gut daran zu erinnern, das Strayex ein vollwertiges Betriebssystem ist das auf echter Hadware laufen kann. Ich rate allerdings davon ab. Um eine Virtuelle Maschine zu konfigurieren kannst du folgende Spezefikationen benutzen:
- 32-bit Prozessor, i386 kompatibel,
- mindestens 32 MB RAM,
- Monitor 80x25 VGA Verbindung, intigrierte Grafikeinheit,
- PS/2 Tastatur,
- Massenspeicher wird in dieser Version nicht benötigt,
