#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include <string.h>  /*Declarations for strcat()*/
#include "flappybird.h"

#define NUMBER_OF_HIGHSCORE 4


/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits. */
void  num32asc(int n)
{
	int i;
	for (i = 28; i >= 0; i -= 4){
		TextString[i] = "ABCDEFGHIGKLMNOBKRSTUVWHYZ"[(n >> i) & 15];
	}

}

// Mohammed 2023-02-28
void Write_score(int score, int name){
    
// compare the score with the highscore value in the memory in zero position is the highest
    int replace_score; // which index to replace
    int i, replace_index;
    for (i = 0; i < NUMBER_OF_HIGHSCORE; i++){ 
        if (score > highscores[i]){  
            replace_index = i;
        }
    }    

    if (replace_index != -1) { // look if there is a score we can change
        highscores[replace_score] = score; // add the new score to the buffer
        highscores[replace_score + 3] = name; // add the new name with the score   
    }
}




// Mohammed 2023-02-28
void read_scoreboard(){
    int i;
    for (i = 0; i < NUMBER_OF_HIGHSCORE; i++)
    {   
        char* str = "Score ";
        IntToCharArray(i);
        char dest[20]={0};
        my_strcat( dest, str );
        my_strcat( dest, TextString );

        str = " : ";
	    IntToCharArray(highscores[i]);
        my_strcat( dest, str );
	    my_strcat( dest, TextString );

        num32asc(highscores[i+3]);
        my_strcat( dest, TextString );
	    display_string(0,dest);
	    display_string(1,TextString);
	    display_update();
	    display_string(0,"");

    }

}














