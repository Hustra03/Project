#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

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

void displayGame()
{
	displayBird()


}

void displayBird(int x, int y)
{}