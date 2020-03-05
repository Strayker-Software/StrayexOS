<h1 align="center">StrayexOS</h1>
<p align="center">
    <a href="https://github.com/StraykerPL/StrayexOS/blob/master/LICENSE"><img src="https://img.shields.io/badge/License-MIT%2FX11-green"></a>
    <a href="https://github.com/StraykerPL/StrayexOS/releases"><img src="https://img.shields.io/github/v/release/StraykerPL/StrayexOS?include_prereleases"></a>
    <img src="https://img.shields.io/github/downloads/StraykerPL/StrayexOS/total?color=green">
</p>
<p align="center">
    <img src="https://img.shields.io/github/issues/StraykerPL/StrayexOS">
    <img src="https://img.shields.io/github/issues-pr/StraykerPL/StrayexOS">
    <img src="https://github.com/StraykerPL/StrayexOS/workflows/Test%20Kernel/badge.svg?branch=master">
</p>

Strayex is 32-bit monotasking operating system with microkernel. Written as hobby OS for mine learning and entertainment reason and for teaching of OS/Dev

<img align="center" src="https://github.com/StraykerPL/StrayexOS/blob/master/strayex-debug.png" alt="Can't load image!">

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

# Gettings Started

1. Get the newest Strayex ISO from [here](https://github.com/StraykerPL/StrayexOS/releases) ("Assets" list) and download it,

2. Open virtual machine app and run VM with this ISO:
   
   - for Virtual Box:
     
     <img align="center" src="" alt="Can't load image!">
     
     For more info, go to `docs` folder!
   
   - for QEMU: `make iso-run-qemu` or just start `qemu-system-x86_64` on your machine,
   
   - for Bochs: `make iso-run-bochs` or just start `bochs`
     
     `Warning!` Bochs can ask for config script, get one from `docs/.bochsrc` in repo or generate one by yourself, also Bochs can ask for disk image to run on, download from `docs/c.img` in repo or ask Bochs to build one.

3. Watch Strayex starts up!

# Design and Distributions

Strayex is designed to be simple (for me and you :) ) to understand and to develop.
I make releases every major changes, small changes are minor. The biggest changes are uploaded as new distributions.

There are two lines of Strayex family of operating systems: Strayex Kernel-based, named StrayexOS and Linux-based, named Strayex Linux. In this repo are saved Strayex Kernel-based systems. For Strayex Linux, there will be another way for contribution.
On [official Strayex side](https://straykerpl.github.io/#Strayex) I will upload all source files of distributions listed below, for mirror.

For quicker work with Strayex, there are other projects for you:

- [Strayex Shell](https://github.com/StraykerPL/StrayexShell) - cross-platform CLI for hobby OSs,

- [Strayex Update Center](https://github.com/StraykerPL/StrayexUpdateCenter) - for managing Strayex repos and ISOs,

Distribution list (Strayex Kernel):

- Strayex Legacy - based on [Bran's Kernel Development Tutorial](http://www.osdever.net/bkerndev/Docs/title.htm),
- Pretorian Alpha 1.0.0,
- Pretorian Alpha 1.0.1,
- Pretorian Alpha 1.1.0 (actually in repository),

# TODO

[List](https://github.com/StraykerPL/StrayexOS/blob/master/docs/TODO.md) of what I would like to be done in StrayexOS and it's repository!

# Contributions

Feel free to contribute to project! Read [CONTRIBUTING.md](https://github.com/StraykerPL/StrayexOS/tree/master/docs) to know how to do it!

# Contact

[My website is here!](https://straykerpl.github.io)

[Join me on Facebook!](https://www.fb.com/straykersoftware)

If you have any suggestions for Strayex or you want to ask me for something, join to [Strayex Discord Server!](https://discord.gg/ytdkCVD)
