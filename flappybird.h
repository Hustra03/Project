int highscore1;
int highscore1;
int highscore1;
char highscore1name[3];
char highscore2name[3];
char highscore3name[3];
int highscores[6];

int menuChoice=0;
int difficulty=0;
int map[128][32];
//define global variabels


#define TRISE  *(volatile unsigned*)(0xbf886100)
#define PORTE  *(volatile unsigned*)(0xbf886110)


void displayMenu();
void displayGame(int birdx, int birdy, double birdspeed, int size);
//define functions for display
void init(void)
//define functions for functions