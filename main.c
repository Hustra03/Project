#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"

int main(void) {

	SYSKEY = 0xAA996655;  
	/* Unlock OSCCON, step 1 */
	
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
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

	//initaialize values 
 	init();
	display_string(0, "KTH/ICT lab");
	display_string(1, "in Computer");
	display_string(2, "Engineering");
	display_string(3, "Welcome!");
	display_update();
	while (1)
	{			
		//Display menu here
		//menu();
		//savetomem();
		break;
	}
	return 0;
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
				 difficulty=3;
				//Hard
				break;
			case 2:
			 difficulty=2;
				//Normal
				break;
			case 3:
				 difficulty=1;
				//Easy
				break;
			case 4:
			    //go back
				menuChoice = 0;
				break;
			}
		}
		displayMenu();
	}
}