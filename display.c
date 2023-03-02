#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "flappybird.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc)
{
	int i;
	for (i = cyc; i > 0; i--)
		;
} // Directly copied from lab 3

uint8_t spi_send_recv(uint8_t data)
{
	while (!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while (!(SPI2STAT & 1));
	return SPI2BUF;
} // Directly copied from lab 3

void displayMenu()
{

	if (currentmenu == 0) // Main Menu
	{
		display_string(0, "1.Start Game");
		display_string(1, "2.High Score");
		display_string(2, "3.Difficulty");
		display_string(3, "4.Help Menu");
	}
	else if (currentmenu == 1) // Change Difficulty
	{
		display_string(0, "1.Current: Easy");
		if (difficulty==2)
		{
			display_string(0, "1.Current: Normal");
		}
		if (difficulty==3)
		{
			display_string(0, "1.Current: Hard");
		}
		
		display_string(1, "2. -- Difficulty");
		display_string(2, "3. ++ Difficulty");
		display_string(3, "4.Back");
	}
	else if (currentmenu == 2) // High Score
	{
		display_string(0, "High Score 1");
		display_string(1, "High Score 2");
		display_string(2, "High Score 3");
		display_string(3, "4.Back");
	}
	else if (currentmenu == 3) // Help
	{
		display_string(0, "Menu - BTN 1-4");
		display_string(1, "Jump - BTN 1/4");
		display_string(2, "x- BTN 3, x+ BTN 2");
		display_string(3, "4. Back");
	}
	return;
}
// Erik Paulinder 2023-02-27	

void displayGame(int ObstacleX[], int ObstacleY[])
{
	int i, j, g; // Declaring for-loop variables
	int yCount = 4;
	int holesize = 0xff;
	if (difficulty == 2)
	{
		holesize = 0x3F;
	}
	if (difficulty == 3)
	{
		holesize = 0x0F;
	}
	//Sets size/value of hole, for this display the binary value is reversed, 1 = 0
	//FF = 8 bits zero, 3F = 6 bits zero, ,0F = 4 bits zero, 
	for (i = 0; i < 4; i++)//Because it will only write on 1/4 of the screen with display image, create it 4 times
	{
		yCount = 4;
		for (j = 0; j < 128; j++)//Fill every position in the array
		{
			for (g = 0; g < 8; g++)//Check each obstacle 
			{
				if ((ObstacleX[g] < (i + 1) * 32) && (ObstacleX[g] > (i * 32)))//Checks if this obstacle x is located in current zone
				{
					if (j % 32 == ObstacleX[g] % 32)//If so, checks that current value ObstacleX is the same as j, in intervall of 32
					{
						if (yCount == 3 && ObstacleY[g] == 4)
						{
							game[j] = holesize;
						}
						else if (yCount == 2 && ObstacleY[g] == 3)
						{
							game[j] = holesize;
						}
						else if (yCount == 1 && ObstacleY[g] == 2)
						{
							game[j] = holesize;
						}
						else if (yCount == 0 && ObstacleY[g] == 1)
						{
							game[j] = holesize;
						}//Above checks so that the hole is placed in correct y-value, aka flag(?)
						else
						{
							game[j] = 0x00;
						}//If not correct y value, but correct x-value, fill the entire thing
					}
					else
					{
						game[j] = 0xFF;
					}//If not correct x, set all to 1, which in display means 0
				}
				if ((birdx < (i + 1) * 32) && (birdx >= (i * 32)))
				{
					if (j % 32 == birdx % 32)
					{
						if (yCount == 3 && (32 > birdy && birdy >= 24))
						{
							if (birdy % 8 == 0)
							{
								game[j] = ~(0x80);
							}
							else
							{
								game[j] = ~(0x80 >> (birdy % 8));
							}
						}
						else if (yCount == 2 && (24 > birdy && birdy >= 16))
						{
							if (birdy % 8 == 0)
							{
								game[j] = ~(0x80);
							}
							else
							{
								game[j] = ~(0x80 >> (birdy % 8));
							}
						}
						else if (yCount == 1 && (16 > birdy && birdy >= 8))
						{
							if (birdy % 8 == 0)
							{
								game[j] = ~(0x80);
							}
							else
							{
								game[j] = ~(0x80 >> (birdy % 8));
							}
						}
						else if (yCount == 0 && (8 > birdy && birdy >= 0))
						{
							if (birdy % 8 == 0)
							{
								game[j] = ~(0x80);
							}
							else
							{
								game[j] = ~(0x80 >> (birdy % 8));
							}
						}
					}
				}//Similar to obstacles, first checks if correct interval of x, then if correct x, then correct y, if so set one pixel, with y value offset from top
			}
			if (j % 32 == 0)
			{
				yCount -= 1;
			}//Increments yCount, for which 1/4 currently located in
			if (yCount==0)
			{
				game[j] = game[j] && (0x01);
			}//Is intended to create a ground, if implemented correctly
			
		}
		display_image(32 * i, game);//Send current array, with current 1/4 of map, to display_image, to show on OLED-Screen
	}
	// Creates a Bit-Map Dependent on current game status, setting obstacle and bird x and y to one.
	// Erik Paulinder 2023-02-27
	return;
}
// Erik Paulinder 2023-02-27
// Above generates a bitmap depending on current game data, and then passes that one to display image

void display_image(int x, const uint8_t *data)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));

		DISPLAY_CHANGE_TO_DATA_MODE;

		for (j = 0; j < 32; j++)
			spi_send_recv(~data[i * 32 + j]);
	}
} // Directly copied from lab 3

void display_init(void)
{
	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
} // Directly copied from lab 3

void display_update(void)
{
	int i, j, k;
	int c;
	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for (j = 0; j < 16; j++)
		{
			c = textbuffer[i][j];
			if (c & 0x80)
				continue;

			for (k = 0; k < 8; k++)
				spi_send_recv(font[c * 8 + k]);
		}
	}
} // Directly copied from lab 3

void display_string(int line, char *s)
{
	int i;
	if (line < 0 || line >= 4)
		return;
	if (!s)
		return;

	for (i = 0; i < 16; i++)
		if (*s)
		{
			textbuffer[line][i] = *s;
			s++;
		}
		else
			textbuffer[line][i] = ' ';
} // Directly copied from lab 3

