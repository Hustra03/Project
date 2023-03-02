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
		if (currentmenu == 0) // Standard/Start menu
		{
			switch (menuChoice)
			{
			case 1:
				gameStart();			 // Starts game with current options
				currentmenu = 3; // jump to menu number 3 when menu is called, which is the gameover men
				break;
			case 2:
				//menuChoice = 1; //Changes menu to difficulty menu //should change in the interrupet depends on the button pressed
				currentmenu = 1; // jump to difficulty menu
				break;
			case 3:
				currentmenu = 2; // jump to highscore menu / Changes menu to high score screen menuChoice = 2;
				break;
			case 4:
				currentmenu = 4;
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
		if (currentmenu == 2) // Highscore menu
		{
			switch (menuChoice)
			{
			case 4: // There is only Case 4, since any the 3 other options (The High Scores) are not interactable with
				currentmenu = 0; //Go back to Start Menu
				break;
			}
		}
		if (currentmenu == 3) // Game Over Menu
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
		if (currentmenu == 4)
		{
			switch (menuChoice)
			{
			case 4: // There is only Case 4, since any the 3 other options (The High Scores) are not interactable with
				currentmenu = 0; //Go back to Start Menu
				break;
			}
		}
		displayMenu();
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
		if (birdy<=0)
		{gametrue=1;}
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
					gametrue =1;// If bird and obstacle[i] do collide, Game Over
				}
			}

		} // Decreases x-value of obstacles by one, how many are used depend on difficulty

		// One Frame of game here
		displayGame(ObstacleX, ObstacleY);//Sends new obstacles to DisplayGame
	}
	//Game is over when this is shown
	display_string(0,"Game Over!");

	char scoreArray[10];
    scoreArray[10] =  IntToCharArray(score);//Converts int score to char[] scoreArray with correct characters. 

	display_string(1,scoreArray);
	display_update();
	delay(100);
	while (getbtns()==0)
	{
		display_string(0,"Game Over!");
		display_string(1,scoreArray);
		display_update();
	}//Shows game over screen until player presses some button, in order to ensure visability
}