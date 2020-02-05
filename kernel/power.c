/*
 Strayex Kernel
 v1.1.0
 Kernel's Power Managment file
 Copyright © 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kpower.h"
#include "klib/kio.h"
#include "klib/kstdlib.h"

void kpoweroff()
{
	koutportw(0x604, 0x2000); // For QEMU,
	koutportw(0x4004, 0x3400); // For VirtualBox,
}