int highscores[9];
//This array stores variabels for high score, int is a 4 byte variabel
//The diffrent positions represents:  0. top score, 1. middle score, 2. lowest stored score
//3. and 4. contains initials for score 1, 5. and 6. contains initials for score 2, 7. and 8. contain initials for score 3

int menuChoice=0;
//This variabel determines which menu should be shown by display menu.
int difficulty=1;
//This variabel represent current game difficulty, changable in the menu

int timecount=0;

#define TRISE  *(volatile unsigned*)(0xbf886100)
#define PORTE  *(volatile unsigned*)(0xbf886110)
//Above redefines ports

void displayMenu();
void displayGame(int birdx, int birdy, double birdspeed, int size);
/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];
//Above defines global functions from display.c 

void init(void);
//define functions from birdfunctions.c