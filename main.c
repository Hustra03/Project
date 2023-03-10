#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include <math.h>
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
	menuChoice = 0;
	delay(1500);
	while (1)
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
			gameStart(); // Starts game with current options
			menuChoice = 0;
			break;
		case 2:
			// Changes menu to difficulty menu //should change in the interrupet depends on the button pressed
			currentmenu = 1; // jump to difficulty menu
			menuChoice = 0;
			break;
		case 3:
			currentmenu = 2; // jump to highscore menu / Changes menu to high score screen menuChoice = 2;
			menuChoice = 0;
			break;
		case 4:
			currentmenu = 3; // help menu to check the controls keys
			menuChoice = 0;
			break;
		}
	}
	if (currentmenu == 1) // Difficulty menu
	{
		switch (menuChoice)
		{
		case 1:
			menuChoice = 0;
			break;
		case 2:
			if (difficulty < 3)
			{
				difficulty += 1;
				menuChoice = 0;
			}
			break;
		case 3:
			if (difficulty > 1)
			{
				difficulty -= 1;
				menuChoice = 0;
			}
			break;
		case 4:
			// Go back to Start Menu
			currentmenu = 0;
			menuChoice = 0;
			break;
		}
	}
	if (currentmenu == 2) // Highscore menu
	{
		switch (menuChoice)
		{
		case 4:
			currentmenu = 0;
			menuChoice = 0;
			break;
		}
	}
	if (currentmenu == 3)
	{
		switch (menuChoice)
		{
		case 4:
			// Go back to Start Menu
			currentmenu = 0;
			menuChoice = 0;
			break;
		}
	}

	return;
}

int next = 0;
int rand(void)
// RAND_MAX assumed to be 32767
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void gameStart(void)
{
	birdx = 10;
	birdy = 32;
	int score = 0;

	int ObstacleX[4] = {31, 63, 95, 127};
	int ObstacleY[4] = {1, 0, 3, 2};
	// Array length no longer dependent on difficulty, now constant?
	// initalize game start values

	int gametrue = 1;
	int lastscore = 5;
	int size = 0;
	int startdifficulty = difficulty;
	if (difficulty == 1)
	{
		size = 8;
	}
	if (difficulty == 2)
	{
		size = 6;
	}
	if (difficulty == 3)
	{
		size = 4;
	}
	int i, j;

	while (gametrue == 1)
	{
		delay(100); // Change to change over time, currently one frame per secound
		if ((((((getbtns() >> 2) & 0x1 == 0x1) || (((PORTF >> 1) & 0x1))) == 0x1)) && birdy <= 31)
		{
			birdy += 1;
		}
		else
		{
			birdy -= 1;
		}
		if (((score) % 20 == 19) && (size > 4)) // Increased difficulty over time, not tested if correctly implemented
		{
			difficulty += 1;
			size -= 2;
		}

		if (birdy == 32) // Checks that player is not above game area
		{
			birdy = 30;
		}
		if (birdy == 0) // Checks that player is not below game area
		{
			gametrue = 0;
		}
		for (i = 0; i < 4; i++) // Performs following for every obstacle
		{
			if (ObstacleX[i] <= 0)
			{
				ObstacleX[i] = 128;
				ObstacleY[i] = (rand() % (3)) + 1;
			} // Checks if obstacle x value is less than zero, if so move to the far right/x=127, and generate a new y-value

			if ((ObstacleX[i] == birdx || ObstacleX[i] == birdx + 1 || ((getbtns() & 0x1) == 0x1 && ((ObstacleX[i] == birdx + 1) || (ObstacleX[i] == birdx + 2))) || (((((getbtns() >> 1) & 0x1) == 0x1) && ((ObstacleX[i] == birdx - 1) || (ObstacleX[i] == birdx))))))
			{ // Checks if player x value equals Obstacle[i] x, and if currently moving, if located one space before or after, in order to avoid wallclipping
				// Erik Paulinder

				if (((birdy) < ((ObstacleY[i]) * 8) + size) && ((birdy) > (ObstacleY[i]) * 8))
				{ // Above controlled collision, if between ObstacleY*8, and ObstacleY*8 + size, then ok, if not game over

					if (lastscore != i)
					{
						score += 1; // If not collison
						lastscore = i;
					}
				}
				else
				{
					gametrue = 0; // Collision, Game Over
				}
			}
			ObstacleX[i] -= 1; // Decreases x-value by one
		}
		if (((getbtns() & 0x1) == 0x1 && birdx < 120)) // Button 2 moves right, if birdx not greater than 120
		{
			birdx += 1;
		}

		if (((((getbtns() >> 1) & 0x1) == 0x1) && (birdx > 5))) // Button 3 moves left, if birdx not less than 0
		{
			birdx -= 1;
		}
		// One Frame of game here
		displayGame(ObstacleX, ObstacleY);
	}
	// Game is over when this is shown
	IntToCharArray(score); // Converts int score to char[] scoreArray with correct characters.
	display_string(0, "Game Over!");
	display_string(1, TextString);
	display_string(2, "");
	display_string(3, "");
	display_update();
	delay(500);

	int highscoretrue = 0;
	int highscoreindex = 0;
	for (i = 0; i < 3; i++)
	{
		if ((score > highscores[i]) && (highscoretrue == 0))
		{
			highscoretrue = 1;
			highscoreindex = i;

			for (j = 3; j < i; j++)
			{
				highscores[j] = highscores[j - 1];
				highscores[j + 3] = highscores[j + 2];
			}
			highscores[highscoreindex] = score;
		}
	}
	difficulty = startdifficulty;
	int initial = 0;
	int initalnumber = 3;

	if (highscoretrue == 1)
	{
		highscores[highscoreindex + 3] = 0;
		while (initalnumber >= 0)
		{
			switch (menuChoice)
			{
			case 1:
				if (initial < 5)
				{
					initial += 1;
				}
				menuChoice = 0;
				break;
			case 2:
				if (initalnumber == 3)
				{
					highscores[highscoreindex + 3] += initial * 1000;
				}
				if (initalnumber == 2)
				{
					highscores[highscoreindex + 3] += initial * 100;
				}
				if (initalnumber == 1)
				{
					highscores[highscoreindex + 3] += initial * 10;
				}
				if (initalnumber == 0)
				{
					highscores[highscoreindex + 3] += initial;
				}
				initial = 0;
				initalnumber -= 1;
				menuChoice = 0;
				break;
			case 3:

				if (initial >= 1)
				{
					initial -= 1;
				}
				menuChoice = 0;
				break;
			}

			display_string(0, "1. Increase Inital");
			display_string(1, "2. Decrease Inital");
			display_string(2, "3. Next Inital");
			if (initial == 0)
			{
				display_string(3, "Current: A");
			}
			if (initial == 1)
			{
				display_string(3, "Current: B");
			}
			if (initial == 2)
			{
				display_string(3, "Current: C");
			}
			if (initial == 3)
			{
				display_string(3, "Current: D");
			}
			if (initial == 4)
			{
				display_string(3, "Current: E");
			}
			if (initial == 5)
			{
				display_string(3, "Current: F");
			}
			display_update();
			delay(100);
		}
	}

	return;
}