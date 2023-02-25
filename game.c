#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"
/* Interrupt Service Routine */
void user_isr(void)
{
	if (((IFS(0) >> 8) & 0x1) == 0x1)//This represents the game moving forward one frame
	{
		T2CON = 0x0; //Stop timer
		if(timecount>=10)
		{

	
		} 
		//Displays mytime using previous code
		IFSCLR(0) = 0x00000100;  // Clear the timer interrupt status flag
		T2CONSET = 0x8070; //Restarts timer with same settings
		timecount += 1;

	}
	if (((IFS(0) >> 15) & 0x1) == 0x1)
	{	
		PORTE += 1; //increases LED value, remove at the end, utalized to show interrupt being called.	
		IFSCLR(0) = 0x00008000;
	}//Old suprise assignment, currently falling edge trigger
	return;
}