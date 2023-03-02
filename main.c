#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include "flappybird.h"



int main(void)
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

	init();
	display_init();
	display_string(0, "Flappy Bird");
	display_string(1, "By:");
	display_string(2, "Erik Paulinder");
	display_string(3, "Mohammed Louai Alayoubi");
	display_update();
	menuChoice=0;
	delay(1500);
	while(1)
	{
		
		displayMenu();
		display_update();
		menu();
	}
	return 0;
}


void menu(void) // the menu should not be run when the game is ongoing
{
		if (currentmenu == 0) // Standard/Start menu
		{
			switch (menuChoice)
			{
			case 1:
				gameStart();// Starts game with current options
				break;
			case 2:
				//Changes menu to difficulty menu //should change in the interrupet depends on the button pressed
				currentmenu = 1; // jump to difficulty menu
				break;
			case 3:
				currentmenu = 2; // jump to highscore menu / Changes menu to high score screen menuChoice = 2;
				break;
			case 4:
				currentmenu = 3; // help menu to check the controls keys
				menuChoice=0;
				break;
			}
		}
		if (currentmenu == 1) // Difficulty menu
		{
			switch (menuChoice)
			{
			case 1:
				difficulty = 3; //Change difficulty to 3/Hard
				break;
			case 2:
				difficulty = 2; //Change difficulty to 2/Normal
				break;
			case 3:
				difficulty = 1; //Change difficulty to 1/Easy
				break;
			case 4:
				//Go back to Start Menu
				currentmenu = 0;
				break;
			}
		}
		if ((currentmenu == 2)) // Highscore menu
		{
			switch (menuChoice)
			{
			case 4:
				currentmenu = 0;
				break;
			}
		}
		if ((currentmenu == 3))
		{
			switch (menuChoice)
			{
			case 4:
				//Go back to Start Menu
				currentmenu = 0;
				break;
			}
		}
		
	return;
}

void gameStart(void)
{
	birdx = 5;//Bird x value, constant 
	birdy = 32; //Bird y inital value, changes over time
	score = 0;
	int i, j;

	int ObstacleX[8] = {31, 63, 95, 127,150,180,210};
	int ObstacleY[8] = {2, 1, 4, 3, 1,2,3,4}; 
	// Array length no longer dependent on difficulty, now constant?
	

	int gametrue = 1;//Determines if it is a game over

	int size= 10-2*difficulty;//Easy = 1, Normal = 2, Hard = 3 => Size = 8, 6, or 4 
	// initalize game start values

	while (gametrue == 1) //This contains one instance of the game, frame per frame
	{
		delay(100); // Change to change over time, currently ten frames per secound

		if (getbtns()!=0x0 && birdy<=32) //Change getbtns to input value
		{
			birdy += 1;
		}
		else
		{birdy -= 1;}//Above checks if the bird should jump or fall

		if (birdy==32) 
		{
			birdy=30;
		}
		if (birdy<=0)
		{gametrue=0;}
		//Above checks if bird is out of bounds, if above simply reduce value, if below game over because the bird has fallen

		for (i = 0; i < 4; i++) //Performs following tasks for each obstacle, x and y values connected
		{
			ObstacleX[i] -= 1; //Increments ObstacleX
			if (ObstacleX[i] < 0)
			{
				ObstacleX[i] = 127;
			}//Checks if X value is 0, if so move to right end of screen, aka 127
			if (ObstacleX[i] == birdx) //Compares X values of bird and obstacle[i]
			{
			
				if ((birdy < ((ObstacleY[i]-1)*8) + size) && (birdy > (ObstacleY[i]-1)*8)) 
				{//Above controlles collision, if between ObstacleY*8, and ObstacleY*8 + size, then ok, if not game over

					score += difficulty; // If bird and obstacle[i] do not collide
				}
				else
				{
					gametrue =0;// If bird and obstacle[i] do collide, Game Over
				}
			}

		} // Decreases x-value of obstacles by one, how many are used depend on difficulty

		// One Frame of game here
		displayGame(ObstacleX, ObstacleY);//Sends new obstacles to DisplayGame
	}
	//Game is over when this is shown
	IntToCharArray(score);//Converts int score to char[] scoreArray with correct characters. 
	display_string(0,"Game Over!");
	display_string(1,TextString);
	display_string(2,"");
	display_string(3,"");
	display_update();

	
	

	delay(100);
	while (getbtns()==0)
	{
		display_string(0,"Game Over!");
		display_string(1,TextString);
		display_string(2,"");
		display_string(3,"");
		display_update();
	}//Shows game over screen until player presses some button, in order to ensure visability


		if (currentmenu == 4) // Game Over Menu
		{
			switch (menuChoice)
			{
			case 1:
				// Increase Inital By One  
				break;
			case 2:
				// Decrease Inital By One  
				break;
			case 3:
				// Go To Next Inital 
			case 4:
				currentmenu = 0;//Go back to Start Menu, Add in a confirm since this prevents entering complete high score initals
				break;
			}
		}
}