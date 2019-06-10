/*
 Strayex Kernel
 v1.0.1
 Kernel Programmable Interrupt Table file
 Copyright 2019 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kdt.h"
#include "klib/kio.h"
#include "klib/kstdlib.h"
#include "klib/ktime.h"
#include <stdbool.h>

// Calculate intercalary year:
bool If_intercalary(int year) {return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));}

// Change timer work mode:
void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    koutportb(0x43, 0x36);             /* Set our command byte 0x36 */
    koutportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    koutportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

// Variables to hold values of system's time:
int kernel_start = 0;
int kernel_seconds = 0;
int kernel_minutes = 0;
int kernel_hours = 0;
int kernel_days = 1;
int kernel_months = 1;
int kernel_years = 1970;
int kticks = 0;

// Functions for changing time values:

// Increment days:
void day_up()
{
	// Checks, if year is intercalary:
	if(If_intercalary(kernel_years))
	{
		if(kernel_months == 2 && kernel_days == 29)
		{
			kernel_days = 0;
			//month_up();
		}
	}
	else
	{
		if(kernel_months == 2 && kernel_days == 28)
		{
			kernel_days = 0;
			//month_up();
		}
	}
	
	// TODO
	//if(kernel_days == 30 && (kernel_months % 2 == 0 || kernel_months % 3 == 0))
}

// Increment hours:
void hours_up()
{
	if(kernel_hours == 23)
	{
		kernel_hours = 0;
		day_up();
	}
	else kernel_hours++;
}

// Increment minutes:
void minutes_up()
{
	if(kernel_minutes != 60) kernel_minutes++;
	else
	{
		kernel_minutes = 0;
		hours_up();
	}
}

// Increment seconds:
void seconds_up()
{
	if(kernel_seconds != 60) kernel_seconds++;
	else
	{
		kernel_seconds = 0;
		minutes_up();
	}
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'kernel_start' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler()
{
	kticks++;
    if (kticks % 18 == 0)
    {
        // Time elapse instructions:
		kernel_start++;
		seconds_up();
    }
}

/* This will continuously loop until the given time has
*  been reached */
void kwait(int ticks)
{
    int eticks;
    eticks = kernel_start + ticks;
    while(kernel_start < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void pit_init()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
