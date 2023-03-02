#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <stdio.h>	 /* Declarations of rand and the like */
#include <string.h>  /*Declarations for strcat()*/
#include "flappybird.h"

#define NUMBER_OF_HIGHSCORE 3
char* NumString[10];
char* CharString[10];

/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits.  lab3*/
void num32asc(int n, int x) // s char, n number and x is flag if this is a number or hexadec 
{
    int i;
    if (x ==1){
        for(i=0;i<NUMBER_OF_HIGHSCORE;i++){
            if (n!=0){
                n = n%100;
                if(n == 10){
                    CharString[i]="A";
                }
                else if(n == 11){
                    CharString[i]="B";
                }
                else if(n == 12){
                    CharString[i]="C";
                }
                else if(n == 13){
                    CharString[i]="D";
                }
                else if(n == 14){
                    CharString[i]="E";
                }
                else if(n == 15){
                    CharString[i]="F";
                }
                n = n/100;
            }
        }
    }
    if (x ==1){
        for(i=0;i<NUMBER_OF_HIGHSCORE;i++){
            n = n%10;
            if  (n == 0){
                NumString[i]= "0";
            }
            else if(n == 1){
                NumString[i]= "1";
            }
            else if(n == 2){
                NumString[i]= "2";
            }
            else if(n == 3){
                NumString[i]= "3";
            }
            else if(n == 4){
                NumString[i]= "4";
            }
            else if(n == 5){
                NumString[i]= "5";
            }
            else if(n == 6){
                NumString[i]= "6";
            }
            else if(n == 7){
                NumString[i]= "7";
            }
            else if(n == 8){
                NumString[i]= "8";
            }
            else if(n == 9){
                NumString[i]= "9";
            }

            n = n/10;
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
        x= 10;
        num32asc(x,1);
        my_strcat( dest, CharString);
        //number = highscores[i];
	    //num32asc(NumString,number);
        //my_strcat( dest, NumString);
	    //my_strcat( dest, TextString );
        //x= highscores[i+3];
        //text32asc(x);
        //my_strcat( dest, NumString);


	    display_string(i,dest);
	    //display_string(i+1,TextString);
	    display_update();
	    //display_string(0,"");

    }

}
















