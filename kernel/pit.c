/*
 Strayex Kernel
 v1.1.0
 Kernel Programmable Interrupt Table file
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#include "klib/kdt.h"
#include "klib/kio.h"
#include "klib/kstdlib.h"
#include "klib/ktime.h"
#include <stdbool.h>

// Calculate intercalary year:
bool If_intercalary(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

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

// Get start time:
int get_start_time() { return kernel_start; }

// Get seconds:
int get_seconds() { return kernel_seconds; }

// Get minutes:
int get_minutes() { return kernel_minutes; }

// Get hours:
int get_hours() { return kernel_hours; }

// Get days:
int get_days() { return kernel_days; }

// Get months:
int get_months() { return kernel_months; }

// Get years:
int get_years() { return kernel_years; }

// Increment years:
void year_up()
{
	kernel_years++;
}

// Increment months:
void months_up()
{
	if(kernel_months == 12)
	{
		kernel_months = 1;
		//year_up();
	}
	else kernel_months++;
}

// Increment days:
void day_up()
{
	if(If_intercalary(kernel_years))
	{
		switch(kernel_months)
		{
			case 1:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 2:
				if(kernel_days == 29)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 3:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 4:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 5:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 6:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 7:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 8:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 9:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 10:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 11:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 12:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
		}
	}
	else
	{
		switch(kernel_months)
		{
			case 1:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 2:
				if(kernel_days == 28)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 3:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 4:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 5:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 6:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 7:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 8:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 9:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 10:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 11:
				if(kernel_days == 30)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
			
			case 12:
				if(kernel_days == 31)
				{
					kernel_days = 1;
					months_up();
				}
				else kernel_days++;
			break;
		}
	}
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
void kwait(int sec)
{
    int eticks;
    eticks = kticks + sec;
    while(kticks < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void pit_init()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
