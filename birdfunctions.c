#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "flappybird.h"

void init(void)
{

	TRISE &= ~0xff;
	TRISD |= 0xFE0;

} // Erik Paulinder

/* Non-Maskable Interrupt; something bad likely happened, so hang */
void _nmi_handler()
{
	for (;;)
		;
} // Directly copied from lab 3

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset()
{

} // Directly copied from lab 3

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap()
{

} // Directly copied from lab 3
