# How to start working with Strayex?

Like it was in README.md written, there are three ways.
First, download ready ISO file with kernel and bootloader.
Second, download ready binary file of kernel called "skern-(wersja).bin" and add it to device with bootloader installed.
Third is building kernel on-your-own and add it to device with bootloader installed.
Fourth is running kernel with parameter -kernel in QEMU.

## Running Strayex

System prepared in this way is ready to work on virtual mashines, like QEMU, VirtualBox or VMware.
Only need to start VM from ISO and it's ready!

It's good to remember, taht Strayex is a full-fledged operating system and can be run on real hardware, but I advice against that.
To configure virtual mashine, here is system's specification:
- 32-bit processor, i386 compatible,
- at least 32 MB RAM,
- monitor 80x25 VGA connection, integrated graphics card,
- PS/2 keyboard,
- mass storage drive is not needed in this version,

Strayex is equipped in monolithic singletasking kernel - Strayex Kernel, which needs informations from bootloader to work.
System's kernel is compatible with [Multiboot Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html) in version 2.0.
Bootloader compatible with this version loads something called Multiboot Information Structure to memory and lefts mashine in defined state.

When after start of system you will see label "Strayex Kernel" and Debug Mode line, it means that system has started.

## First steps in Strayex

Actual distribution - StrayexOS Pretorian, is in very early state of development and don't have shell.
There's a simple reason - Strayex Kernel can't serve it.
Basic works like writting on screen can be performed with no problem.
To perform some extra exercises, kernel's code have to be edited and compiled again.

## What's next?

Strayex is in very early state of development, so it don't have functionality at all.
To know what will be added to project, look at [TODO.md](https://github.com/StraykerPL/StrayexOS/blob/master/docs/TODO.md).

Now you have basic informations about Strayex! Go to [BASIC.md](https://github.com/StraykerPL/StrayexOS/blob/master/docs/en/BASIC.md) to continue.
