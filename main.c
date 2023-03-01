#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include "flappybird.h"

char textstring[] = "text, more text, and even more text!";

int birdx = 5;
int birdy = 50;

int main(void)
{
	init();
	display_string(0, "Flappy Bird");
	display_string(1, "By:");
	display_string(2, "Erik Paulinder");
	display_string(3, "Mohammed Louai Alayoubi");
	display_update();
	delay(100);
	while(1)
	{
		menu();
	}
	return 0;
}


void menu(void) // the menu should not be run when the game is ongoing
{
	int button1 = 0; // Change to current binary value of input from button 1
	if (button1 != 0)
	{
		if (currentmenu == 0) // Standard menu
		{
			switch (menuChoice)
			{
			case 1:
				game();			 // Starts game with current options
				currentmenu = 3; // jump to menu number 3 when menu is called, which is the gameover men
				break;
			case 2:

				currentmenu = 2; // jump to highscore menu / Changes menu to high score screen menuChoice = 2;
				break;
			case 3:
				// menuChoice = 1; //Changes menu to difficulty menu //should change in the interrupet depends on the button pressed
				currentmenu = 1; // jump to difficulty menu
				break;
			case 4:
				// Help Menu
				break;
			}
		}
		if (currentmenu == 1) // Change to difficulty menu
		{
			switch (menuChoice)
			{
			case 1:
				difficulty = 3;
				// Hard
				break;
			case 2:
				difficulty = 2;
				// Normal
				break;
			case 3:
				difficulty = 1;
				// Easy
				break;
			case 4:
				// go back
				// menuChoice = 0;
				currentmenu = 0; // move back to mainmenu
				break;
			}
		}
		if (currentmenu == 2) // Change to highscore menu
		{
			switch (menuChoice)
			{
			case 1:
				// scroll down in the scorelist if needed
				break;
			case 2:
				// go back
				// menuChoice = 0;
				currentmenu = 0;
				break;
			}
		}
		displayMenu();
	}
	return;
}

void game(void)
{
	birdx = 5;//Bird x value, constant 
	birdy = 32; //Bird y inital value, changes over time
	int score = 0;
	int i, j;

	int ObstacleX[8] = {31, 63, 95, 127,150,180,210};
	int ObstacleY[8] = {2, 1, 4, 3, 1,2,3,4}; 
	// Array length no longer dependent on difficulty, now constant?
	

	int gametrue = 0;//Determines if it is a game over

	int size= 10-2*difficulty;//Easy = 1, Normal = 2, Hard = 3 => Size = 8, 6, or 4 
	// initalize game start values

	while (gametrue == 0) //This contains one instance of the game, frame per frame
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
		if (birdy==0)
		{gametrue=1;}
		//Above checks if bird is out of bounds, if above simply reduce value, if below game over because the bird has fallen

		for (i = 0; i < 4; i++) //Performs following tasks for each obstacle, x and y values connected
		{
			ObstacleX[i] -= 1; //Increments ObstacleX
			if (ObstacleX[i] < 0)
			{
				ObstacleX[i] = 127;
			}
			if (ObstacleX[i] == birdx)
			{
				

				if ((birdy < ((ObstacleY[i]-1)*8) + size) && (birdy > (ObstacleY[i]-1)*8)) 
				{//Above controlled collision, if between ObstacleY*8, and ObstacleY*8 + size, then ok, if not game over

					score += 1; // If not collison
				}
				else
				{
					gametrue =1;// Collision, Game Over
				}
			}

		} // Decreases x-value of obstacles by one, how many are used depend on difficulty

		// One Frame of game here
		displayGame(ObstacleX, ObstacleY);
	}
	display_string(0,"Game Over!");

	int rem, n;
	char scoreArray[10];
	n = score;
    for (i = 0; i < 10; i++)
    {
        rem = n % 10;
        n = n / 10;
        scoreArray[10 - (i + 1)] = rem +'0';
    }
    scoreArray[10] = '\0';

	display_update();
	delay(100);
	while (getbtns()==0)
	{
		display_string(0,"Game Over!");
		display_string(1,scoreArray);
		display_update();
	}
	
}