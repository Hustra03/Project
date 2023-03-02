#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include <string.h>  /*Declarations for strcat()*/
#include "flappybird.h"

#define NUMBER_OF_HIGHSCORE 4

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
    char* scorePointer;
    char* StringToBePrinted;
    char* TextString;
    for (i = 0; i < NUMBER_OF_HIGHSCORE; i++)
    {
        scorePointer= IntToCharArray(highscores[i]);
        StringToBePrinted = "Score ";
        TextString = IntToCharArray(i);
        strcat(StringToBePrinted , TextString);//strcat appends char[] 1 with char[] 2, also removes null charachter from first array
        TextString = " : ";
        strcat(StringToBePrinted , TextString);
        strcat(StringToBePrinted , scorePointer);

        TextString = " "; 
        scorePointer = IntToCharArray(highscores[i + 3]);
        strcat(StringToBePrinted , TextString);
        strcat(StringToBePrinted , scorePointer);

        display_string(i,StringToBePrinted);// display the scorelist
    }

}














