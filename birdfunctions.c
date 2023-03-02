#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "flappybird.h"

char* IntToCharArray(int i)//Warning, length = 10;
{
	int rem, n;
	n = score;
	char Array[10];
    for (i = 0; i < 10; i++)
    {
        rem = n % 10;
        n = n / 10;
        Array[10 - (i + 1)] = rem +'0';
    }
	return Array;
}


void init(void)
{

	SYSKEY = 0xAA996655;
	/* Unlock OSCCON, step 1 */

	SYSKEY = 0x556699AA; /* Unlock OSCCON, step 2 */
	while (OSCCON & (1 << 21))
		;				  /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while (OSCCON & (1 << 21))
		;		  /* Wait until PBDIV ready */
	SYSKEY = 0x0; /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	// Erik Paulinder
	// initaialize values

	TRISE &= ~0xff;
	TRISD |= 0xFE0;

	// Mohammed 
	// btn1 init
	TRISF = 0x2;

	//timer 3 intterupt timer for buttons
	T3CON = 0x0;
	TMR3  = 0X0;
	PR3   = 0xfAf00;
	T3CONSET = 0x8070; 
	IFSCLR(0) = 0x00001000; // clear the interrupt flag
	IPCSET(3) = 0x0000001F; //
	IECSET(0) = 0x00001000; // 

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
