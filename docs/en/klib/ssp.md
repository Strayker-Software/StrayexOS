# Kernel Stack Smash Protector

"ssp.c" file is code for stack "smashing" protection. It's work is simple, functon stops system when any system's function overflow the stack, or when it's pushed too big value on it.

SSP prevents future system work, through entering endless loop and inform user. The only solution is to restart computer and find function, that made system's instability.

If this problem will be repeated, report issue in repository.

## Definitions

None.

## Functions

- void attribute((noreturn)) __stack_chk_fail(void)

Function stops system because of system's instability.

Arguments: none,

Returns: function isn't returning to caller, it's loops for ever,
