#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "flappybird.h"

void displayMenu()
{

	if(menuChoice == 0)
	{
		/*display main menu */
	}
	if (menuChoice == 1)
	{
		/*display high score */
	}
	if (menuChoice == 2)
	{
		/*display game difficulty */
	}
	if (menuChoice == 3)
	{
		/*display control info */
	}
}

void displayGame(birdx, birdy)
{
//This will change the map array, to display current game state
//[0][0] is equal to top-left of screen.

}
