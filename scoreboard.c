#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include <string.h>  /*Declarations for strcat()*/
#include "flappybird.h"

#define NUMBER_OF_HIGHSCORE 3
char* NumString;
char* CharString;

/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits.  lab3*/
void numtohexa(int n, int x) // s char, n number and x is flag if this is a number or hexadec 
{
    int i;
    if (x ==1){
            if (n!=0){

                if(n == 10){
                    CharString="A";
                }
                else if(n == 11){
                    CharString="B";
                }
                else if(n == 12){
                    CharString="C";
                }
                else if(n == 13){
                    CharString="D";
                }
                else if(n == 14){
                    CharString="E";
                }
                else if(n == 15){
                    CharString="F";
                }

            }
        }
    if (x ==0){
            if  (n == 0){
                NumString= "0";
            }
            else if(n == 1){
                NumString= "1";
            }
            else if(n == 2){
                NumString= "2";
            }
            else if(n == 3){
                NumString= "3";
            }
            else if(n == 4){
                NumString= "4";
            }
            else if(n == 5){
                NumString= "5";
            }
            else if(n == 6){
                NumString= "6";
            }
            else if(n == 7){
                NumString= "7";
            }
            else if(n == 8){
                NumString= "8";
            }
            else if(n == 9){
                NumString= "9";
            }

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
    int number;
    int x,j;
    char* boardnum;
    for (i = 0; i < NUMBER_OF_HIGHSCORE; i++)
    {

	    char* str = "Score";
	    //num32asc(boardnum,(i+1));

        if ((i+1) == 1){
            boardnum ="1";
        }else if ((i+1)==2)
        {
            boardnum ="2";
        }else if ((i+1)==3){
            boardnum ="3";
        }
        
	    char dest[20]={0};
	    my_strcat( dest, str );
	    my_strcat( dest, boardnum);
        str = ":";
        my_strcat( dest, str );
        x= highscores[i+3];
        int j = 4;
        while (j !=0)
        {
            x = x%100;
            numtohexa(x,1);
            my_strcat( dest, CharString); 
            x = x/100;
            j--; 
        }

        number = highscores[i];
        j = 4;
        while (j !=0)
        {
            number = number%100;
	        numtohexa(number,0);
            my_strcat( dest, NumString);
            number = number/100;
            j--; 
        }

	    display_string(i,dest);
	    display_update();
    }

}
















