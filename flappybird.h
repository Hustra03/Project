


#ifndef HEADERFILE_H 
#define HEADERFILE_H 


extern int menuChoice; // this varuabel determines which choice been taken means the button that been pressed
extern int currentmenu;
// This variabel determines which menu should be shown by display menu.

extern int highscores[6];
// The diffrent positions represents:  0. top score, 1. middle score, 2. lowest stored score
// 3. contains initials for score 1, 4. contains initials for score 2, 5. contain initials for score 3

extern int difficulty;
// This variabel represent current game difficulty, changable in the menu

extern int birdx;
int birdy;
//These represent current bird x and y values 

extern int score;
//This represents score of current/last game

extern char textstring[];
//Text string for debug purposes

extern char textbuffer[4][16];
/* Declare text buffer for display output */
void delay(int);
void time2string(char *, int);
void quicksleep(int cyc);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void displayGame(int ObstacleX[], int ObstacleY[]);
void displayMenu(void);
void display_image(int x, const uint8_t *data); 	
// Above defines global functions from display.c

void init(void);
char* IntToCharArray(int i);
void _nmi_handler();
void _on_reset();
void _on_bootstrap();
// define functions from birdfunctions.c

void menu(void);
void gameStart(void);
//Define global functions from main.c

extern uint8_t game[512];

extern const uint8_t const font[] ;/* Declare bitmap array containing font */



#endif // end HEADERFILE_H 