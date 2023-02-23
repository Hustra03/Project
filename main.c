#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"

int main(void) {

	//initaialize values 
 	init();

	while (1)
	{
		//Display menu here
		menu();
		savetomem();
	}
}


int game(int mode)
{
	int birdx = 10;
	int birdy = 10;
	int birdspeed = 1; 
	int size = 5 - mode; //initalize game start values 
	int distance = 8 - mode;
	int score = 0;
	
	// 5, 5 mellan obstacles, vilket �r 1 i position 31 
	while(1==1)
	{ 
	birdy + birdspeed; 
	displayGame(birdx, birdy,birdspeed,size,distance, score, map);
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
				game(difficulty); //Starts game with current options
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