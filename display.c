#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
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
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}//Directly copied from lab 3

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}//Directly copied from lab 3


void displayMenu()
{

	if(currentmenu == 0)
	{
		/*display main menu */
	}
	if (currentmenu == 1)
	{
		/*display high score */
	}
	if (currentmenu == 2)
	{
		/*display game difficulty */
	}
	if (currentmenu == 3)
	{
		/*display gameover menu */
	}
	if (currentmenu == 4)
	{
		/*display control info */
	}
	return;
	display_update();
}
//Erik Paulinder 2023-02-27

void displayGame(int birdx, int birdy, int ObstacleX[], int ObstacleY[])
{
int game[128];

for(int i = 0;i<2 + difficulty;i++)
{
	int minus =0;
	for(int i = ObstacleY[i];i< 5+ObstacleY[i]- difficulty;i++)
	{
		minus += 2^i;
	}
	game[ObstacleX[i]]= 255 - minus;
}//Erik Paulinder 2023-02-27

if(game[birdx]>2^birdy)
{
	if(game[birdx]=2^birdy)
	{/*Do Nothing*/}
	int controller=0;
	int count=1;
	while (game[birdx]>2^birdy)
	{
		controller=2^(birdy+count);
		if(game[birdx]=2^birdy)
		{
		break;//End Loop
		}
		if(game[birdx]>controller)
		{
		}
		if(game[birdx]<controller)
		{
		game[birdx]+=2^birdy;
		}
	}//This checks if some pixel above is true,if so increase with 2^birdy, the specific pixel is true, do nothing, or if the value is lower, den increase with 2^birdy
	
}//Erik Paulinder 2023-02-27
else
{
	game[birdx]+=2^birdy;
}

display_image(0,game);
display_update();
return;
}
//Above generates a bitmap depending on current game data, and then passes that one to display image
//Erik Paulinder 2023-02-27


void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 32; j++)
			spi_send_recv(~data[i*32 + j]);
	}
}//Directly copied from lab 3


void display_init(void) {
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
}//Directly copied from lab 3

void display_update(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}//Directly copied from lab 3


void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}//Directly copied from lab 3

/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits. */
static void num32asc( char * s, int n ) 
{
  int i;
  for( i = 28; i >= 0; i -= 4 )
    *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}