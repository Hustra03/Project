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



char *my_strcat(char *s1, const char *s2)
{
    //Pointer should not null pointer
    if((s1 == NULL) && (s2 == NULL))
        return NULL;
    //Create copy of s1
    char *start = s1;
    //Find the end of the destination string
    while(*start != '\0')
    {
        start++;
    }
    //Now append the source string characters
    //until not get null character of s2
    while(*s2 != '\0')
    {
        *start++ = *s2++;
    }
    //Append null character in the last
    *start = '\0';
    return s1;
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
        my_strcat(StringToBePrinted , TextString);//strcat appends char[] 1 with char[] 2, also removes null charachter from first array
        TextString = " : ";
        my_strcat(StringToBePrinted , TextString);
        my_strcat(StringToBePrinted , scorePointer);

        TextString = " "; 
        scorePointer = highscores[i + 3];
        my_strcat(StringToBePrinted , TextString);
        my_strcat(StringToBePrinted , scorePointer);

        display_string(i,StringToBePrinted);// display the scorelist
    }

}














