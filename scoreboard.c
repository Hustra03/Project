#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include "flappybird.h"

#define NUMBER_OF_HIGHSCORE 4
#define High_Score[9]; // 3 HIGHSCORES IN THE LIST

// Mohammed 2023-02-28
void Write_score(int score, int name){
    
// compare the score with the highscore value in the memory in zero position is the highest
    replace_score = -1; // which index to replace
    int i;
    for (i = 0; i < NUMBER_OF_HIGHSCORE; i++){ 
        if (score > High_Score[i]){  
            replace_index = i;
        }
    }    

    if (replace_index != -1) { // look if there is a score we can change
        High_Score[replace_score] = score; // add the new score to the buffer
        High_Score[replace_score + 3] = name; // add the new name with the score   
    }
}

// Mohammed 2023-02-28
void read_scoreboard(){
    int i;
    for (i = 0; i < NUMBER_OF_HIGHSCORE; i++)
    {
       display_string(i + ". " + High_Score[i + 3] + " "+ High_Score[i] + "/n"); // display the scorelist

    }

}














