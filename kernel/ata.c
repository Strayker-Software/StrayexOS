/*
 Strayex Kernel
 v1.1.0
 Kernel's simple ATA DMA storage driver
 Copyright © 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kdisk.h"
#include "klib/kstddef.h"
#include "klib/kstdlib.h"
#include <stdbool.h>

// Variables:
int DiskType = 0x0; // What type is this disk?
int LBA = 0x0;

// Send command to ATA controller, use this function for mechanical help only:
void ata_send_command(int addr, int cmd)
{

}

// Write given data to ATA disk:
bool ata_write(int data)
{
	return true;
}

// Read loaded data from ATA disk:
bool ata_read()
{
	return true;
}

// Driver initialisation:
bool ata_init(int disk_type)
{
	if(disk_type != 0 || disk_type != NULL)
	{
		DiskType = disk_type; // Set given disk type,
		koutportb(0x1F4, LBA); // Get LBA value,
		return true;
	}
	
	return false;
}