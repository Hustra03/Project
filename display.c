#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"

void display( int menu)
{

	if(menu == 0)
	{/*display main menu */}
	if (menu == 1)
	{/*display high score */
	}
	if (menu == 2)
	{/*display game difficulty */
	}
	if (menu == 3)
	{/*display control info */
	}
}

void displayGame(birdx, birdy)
{
	displayBird(birdx,birdy);


}

void displayBird(int x, int y)
{

//Set 

}