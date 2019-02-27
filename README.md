# StrayexOS
Strayex is 32 bit monotasking operating system with monolithic kernel. Written as hobby OS for mine learning and entertainment reason and for teaching of OS/Dev!

# Genesis
As a programmer, I always wanted to create my own operating system, not for main software for computers like Windows and macOS, or Linux. So I started to make simulators of OS's shell in C++ and I understood it's not so hard to write some low-level software.
I wasn't right, but I had a bit of truth. When I looked on Linux Kernel source code, I was afraid of amount of code and complicated functions. But I was determined to achieve my goal and I started to read processors' documentations, forums and tutorials. Finally, I am able to write all code of my OS and show it to another people. I want to show, that OS can be simple in code but powerful and, of course, our own.

# Usage of system
Strayex is designed to run on virtual machines, QEMU, VirtualBox, VMware etc. It's hobby OS, so I designed it on popular VM apps.
OS is not tested on real hardware, because of it's drivers set.
To use Strayex on VM, just download .ISO file from "docs" folder and boot up machine from it, or build OS by yourself on Linux or Windows.
Provided build script is on Linux and need i386-elf-GCC cross-compiler and i386-elf-ld cross-linker to run.
Read COMPILING.md for tutorial, how do it properly.

# Design and Distributions
Strayex is designed to be simple (for me and you :) ) to understand and to develop.
I make releases every major changes, small changes are minor. The biggest changes are uploaded as new distributions.
In GitHub repository I use "experimental" branch to upload code, that may cause unexpected behavior. If you want to use Strayex without working on it's code, don't download this branch and it's ISO file!
On [official Strayex side](http://www.strayex.cba.pl) I uploaded all source files of distributions listed below, for mirror.
This software is released under [GNU General Public License](https://github.com/StraykerPL/StrayexOS/blob/master/LICENSE)!

Distribution list:
- Pretorian Alpha 1.0.0.0 (actually in repository),

# TODO
[List](https://github.com/StraykerPL/StrayexOS/blob/master/docs/TODO.md) of what I would like to be done in StrayexOS and it's repository!

# Contributions
Feel free to contribute to project! Read CONTRIBUTING.md in "docs" folder to know how to do it!
