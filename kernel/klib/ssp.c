/*
	Strayex Kernel Stack Smash Protector
	v1.0.1
	From wiki.osdev.org
*/

// Libraries
#include <stdint.h>
#include "kstdlib.h"

// Checks if macro for stack guard in compilation process:
#if UINT32_MAX == UINTPTR_MAX
	#define STACK_CHK_GUARD 0xe2dee396
#else
	#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

// Takes choosen value to variable:
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

// Protector's function, it's no return type:
void __attribute__((noreturn)) __stack_chk_fail(void)
{
	// Checks for stack smash:
	#if __STDC_HOSTED__
		abort();
	#elif __is_myos_kernel
		panic("Stack smashing detected!");
	#endif

	for(;;);
}