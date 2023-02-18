#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

int highscore1;
int highscore1;
int highscore1;
char highscore1name[3];
char highscore2name[3];
char highscore3name[3];

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
	int map[128][32];// 5, 5 mellan obstacles, vilket �r 1 i position 31 
	while(1==1)
	{ 
	

	displayGame(birdx, birdy,size,distance, score);
	}
}

void menu(void)
{ 
	int menuchoose=0;
	int button1 = 0; //Change to current binary value of input from button 1
	if (button1 != 0 && menuchoose==0)
	{
		if(0)
		{
		switch (menuchoose)
			{
			case 1:
				startgame();
				break;
			case 2:
				highscore();
				menuchoose = 2;
				break;
			case 3:
				changeifficulty();
				menuchoose =1;
				break;
			case 4:
				break;
			}
		}
		if(1)//Change difficulty menu
		{
			switch (menuchoose)
			{
			case 1:
				startgame();
				break;
			case 2:
				highscore();
				menuchoose = 2;
				break;
			case 3:
				changeifficulty();
				menuchoose =1;
				break;
			case 4:
				break;
			}
		}
	}
}