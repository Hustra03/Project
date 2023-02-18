#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int highscore1;
int highscore1;
int highscore1;
char[3] highscore1name;
char[3] highscore2name;
char[3] highscore3name;

int main(void) {

	//initaialize values 

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
	int size = 5 - mode; //initalize game start values 
	int distance = 8 - mode;
	int score = 0;
	bool[128][32] map;// 5, 5 mellan obstacles, vilket är 1 i position 31 
	while()
	{ 
	

	displayGame(birdx, birdy,size,distance, score);
	}
}

void menu(void)
{ 
	menuchoose=0
	if (button != 0 && menuchoose==0)
	{
		if(0)
	
		switch (case)
		case 1:
			startgame();
			break;
		case 2:
			highscore();
			menuchoose = 2
			break;
		case 3:
			changeifficulty();
			menuchoose =1
			break;
		case 4:
			break;
		if(1)
	}
}