#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "flappybird.h"


char* my_strcat(char *s1, const char *s2)
{
    //Pointer should not null pointer
    if((s1 == '\0') && (s2 == '\0'))
        return '\0';
    //Create copy of s1
    char *start = s1;
    //Find the end of the destination string
    while(*start != '\0')
    {
        start++;
    }
    //Now append the source string characters
    //until not get null character of s2
    while(*s2 != '\0')
    {
        *start++ = *s2++;
    }
    //Append null character in the last
    *start = '\0';
    return s1;
}//Copied from online, since problems appeard with importing this function
void IntToCharArray(int i)//Warning, length = 10;
{
	int rem, n;
	n = i;
    for (i = 0; i < 10; i++)
    {
        rem = n % 10;
        n = n / 10;
        TextString[9 - i] = rem +'0';
    }
	return;
}//Puts int i in to TextString as chars backwards, aka 1 = 000000001


void init(void)
{
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
	enable_interrupt();
	return;
} //The initialization function of the program
// Erik Paulinder

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
