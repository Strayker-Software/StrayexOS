# StrayexOS

Strayex is 32-bit monotasking operating system with microkernel. Written as hobby OS for mine learning and entertainment reason and for teaching of OS/Dev![strayex](https://i.pinimg.com/originals/52/ca/5d/52ca5d858273f97588427edbcbd5cf21.jpg)
This project is the best mile stone in learning operating systems development, between [MikeOS](http://mikeos.sourceforge.net/) and [Linux](https://github.com/torvalds/linux)!
As MikeOS explains, how Assembly OSes works, Strayex shows work of similar software but with C language base of kernel. This similarity gives you opportunity to start with MikeOS, go to Strayex and finally study Linux.
Passing that all three projects and learn at least basics will give you opportunity to create your own low-level software. It doesn't have to be howl OS, It can be boot loader, file system, kernel, whatever.

So if you are still interested in look up here:

- [MikeOS](http://mikeos.sourceforge.net/),
- [OSDev Wiki](https://wiki.osdev.org/Main_Page),
- [Bona Fide OS Developer](http://www.osdever.net/),
- [The Linux Kernel](https://github.com/torvalds/linux),

# Genesis

As a programmer, I always wanted to create my own operating system, not as main software for computers like Windows and macOS, or Linux. So I started to make simulators of OS's shell in C++ and I understood it can't be so hard to write some low-level software.
I wasn't right, but I had a bit of truth. When I looked on Linux Kernel source code, I was afraid of amount of code and complicated functions. But I was determined to achieve my goal and I started to read processors' documentations, forums and tutorials.
I found MikeOS and I studied the code of kernel, MikeOS creator's tutorial and I understood how it works.
Finally, I am able to write almost all code of my OS and show it to another people. I want to show, that OS can be simple in code but powerful and our own.
Now I'm able to understand Linux and learn it more easier.

# Usage of system

Strayex is designed to run on virtual machines, QEMU, VirtualBox, VMware etc. It's hobby OS, so I designed it on popular VM apps.
OS is not tested on real hardware, because of it's drivers set.
To use Strayex on VM, just download .ISO file from "docs" folder and boot up machine from it, or build OS by yourself on Linux or Windows.
Provided build script is on Linux and need some additional apps listed in Makefile to run.

# Design and Distributions

Strayex is designed to be simple (for me and you :) ) to understand and to develop.
I make releases every major changes, small changes are minor. The biggest changes are uploaded as new distributions.
In GitHub repository I use "experimental" branch to upload code, that may cause unexpected behavior. If you want to use Strayex without working on it's code, don't download this branch and it's ISO file!
On [official Strayex side](http://www.strayex.cba.pl) I will upload all source files of distributions listed below, for mirror.
This software is released under [MIT/X11 license](https://github.com/StraykerPL/StrayexOS/blob/master/LICENSE)!

Distribution list:

- Strayex Legacy - based on [Bran's Kernel Development Tutorial](http://www.osdever.net/bkerndev/Docs/title.htm),
- Pretorian Alpha 1.0.0,
- Pretorian Alpha 1.0.1 (actually in repository),

# TODO

[List](https://github.com/StraykerPL/StrayexOS/blob/master/docs/TODO.md) of what I would like to be done in StrayexOS and it's repository!

# Contributions

Feel free to contribute to project! Read CONTRIBUTING.md in "docs" folder to know how to do it!
