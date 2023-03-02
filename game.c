#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "flappybird.h"

int timecount = 0;
// needed for buttons intterupt 
#define DEBOUNCE_TIME  10000  // debounce time in ms
int LastButtonTime =0; 
int startgame =0;


/* Interrupt Service Routine */
void user_isr(void)
{
	if (((IFS(0) >> 8) & 0x1) == 0x1) // This represents the game moving forward one frame
	{
		T2CON = 0x0; // Stop timer
		if (timecount >= 10)
		{
			timecount = 0;
		}
		// Displays mytime using previous code
		IFSCLR(0) = 0x00000100; // Clear the timer interrupt status flag
		T2CONSET = 0x8070;		// Restarts timer with same settings
		timecount += 1;
	}
	if (((IFS(0) >> 15) & 0x1) == 0x1)
	{
		PORTE += 1; // increases LED value, remove at the end, utalized to show interrupt being called.
		IFSCLR(0) = 0x00008000;
	} // Old suprise assignment, currently falling edge trigger


		// Mohammed 
	if (((IFS(0)>> 12) & 0x1) == 0x1){ // 

		int TimeSinceLastEvent = TMR3 - LastButtonTime;
		if(TimeSinceLastEvent > DEBOUNCE_TIME){ // debounce time to make sure when the button debounce will not be counted

			if (startgame == 1){ // the game started means use just one button to controll the bird
				if ((getbtns() & 0x1) == 0x1){
				
					PORTE += 1;
				}
			}
			else {
				if ((getbtns() & 0x1) == 0x1){ //btn2
					
					menuChoice = 2;
				}
				else if (((getbtns() >> 1) & 0x1) == 0x1)//btn3
				{
					menuChoice = 3;
				}
				else if (((getbtns() >> 2) & 0x1) == 0x1)//btn4
				{
					menuChoice = 4;
				}
				else if (((PORTF>> 1) & 0x1) == 0x1) //btn1
				{
					menuChoice = 1;
				}
				
			}
			LastButtonTime = TMR3;
		} // btns for menu and game in an tm3 intterupt
	

		
        IFSCLR(0) = 0x00001000;
    }


	return;
}