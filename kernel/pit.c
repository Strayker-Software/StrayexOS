/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Global Descriptor Table management
*
*  Notes: No warranty expressed or implied. Use at own risk.

   Strayex Kernel Global Descriptor Table
   THIS IS NOT MY CODE!
   This file was a little rewritten only, by me,
   this is why I included above copyright header.
   I'm not a copyright holder.
*/

#include "klib/kdt.h"
#include "klib/kio.h"
#include "klib/kstdlib.h"

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    koutportb(0x43, 0x36);             /* Set our command byte 0x36 */
    koutportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    koutportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler()
{
    /* Increment our 'tick count' */
    timer_ticks++;
	
    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 18 == 0)
    {
        //kprintf("One second has passed\n");
    }
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks)
{
    long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void pit_init()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
