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
		// Mohammed 
	if (((IFS(0)>> 12) & 0x1) == 0x1)
	{ // 

		int TimeSinceLastEvent = TMR3 - LastButtonTime;
		if(TimeSinceLastEvent > DEBOUNCE_TIME){ // debounce time to make sure when the button debounce will not be counted

			if (startgame == 1){ // the game started means use just one button to controll the bird
				if ((getbtns() & 0x1) == 0x1){
				
					PORTE += 1;
				}
			}
			else {
				if ((getbtns() & 0x1) == 0x1){ //btn2
					
					menuChoice = 3; PORTE += 1;
				}
				else if (((getbtns() >> 1) & 0x1) == 0x1)//btn3
				{
					menuChoice = 2; PORTE += 1;
				}
				else if (((getbtns() >> 2) & 0x1) == 0x1)//btn4
				{
					menuChoice = 4; PORTE += 1;
				}
				else if (((PORTF >> 1) & 0x1) == 0x1) //btn1
				{
					menuChoice = 1;PORTE += 1;
				}
				
			}
			LastButtonTime = TMR3;
		} // btns for menu and game in an tm3 intterupt
	
        IFSCLR(0) = 0x00001000;
    }

	return;
}