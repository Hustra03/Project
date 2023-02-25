#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"

int main(void) {
char textstring[] = "text, more text, and even more text!";


	//initaialize values 
 	init();
	display_string(3, textstring);
	display_update();
	while (1)
	{			
		//Display menu here
		//menu();
		//savetomem();
	}
}


int game(void)
{
	int birdx = 10;
	int birdy = 10;
	int size = 5 - difficulty; 
	int distance = 8 - difficulty;
	int score = 0;

	int ObstacleX[5];
	int ObstacleY[5];//Do not use whole array, 3 on difficulty 1(easy), 4 on difficulty 2(normal) and 5 on difficulty 3(hard).
	//initalize game start values 

	
	int gametrue=1;
	
	T2CON = 0x0;
	TMR2 = 0x0;
	PR2 = 0x4C4B4;
	IFSCLR(0) = 0x00000100; // Clear the timer interrupt status flag
	IECSET(0) = 0x00000100; //Interrupt Enable Control */
	T2CONSET = 0x8070;
	//Initalized timer for the game
	while(gametrue==0)
	{ 
	}
}

void menu(void)
{ 
	int button1 = 0; //Change to current binary value of input from button 1
	if (button1 != 0 && menuChoice==0)
	{
		if(0)//Standard menu
		{
		switch (menuChoice)
			{
			case 1:
				game(); //Starts game with current options
				break;
			case 2:
				highscore();//Changes menu to high score screen
				menuChoice = 2;
				break;
			case 3:
				changeifficulty();
				menuChoice =1; //Changes menu to difficulty menu
				break;
			case 4:
				break;
			}
		}
		if(1)//Change to difficulty menu
		{
			switch (menuChoice)
			{
			case 1:
				//increase difficulty
				break;
			case 2:
				//decrease difficulty
				break;
			case 3:
				//go back
				menuChoice =0;
				break;
			case 4:
			    //???
				break;
			}
		}
		displayMenu();
	}
}