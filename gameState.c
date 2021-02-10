#include "config.h"
#include "clearScreen.h"
#include "clearGameArray.h"
#include "arrays.h"
#include "splashScreen.h"
#include "writeMatrix.h"
#include "printDigit.h"
#include "paddleMove.h"
#include "configTMR0.h"
#include "configTMR1.h"
#include <stdio.h>
uchar gameState(uchar state, uchar colOne, uchar colTwo)
{                                           // PONG FSM
    uchar row, col = 0;
  //  uchar paddlePos = 3;// paddlePos can be 1-6, low lowest position, 6 highest position
    switch(state)
    {
        case 0:
            state = 1;// reset state
            break;
        case 1:
            clearScreen();
            splashScreen(splishR, splishL);// display "PONG" for 2 sec
            __delay_ms(2000);
             clearScreen();
            state = 2;
            break;
        case 2 :
            splashScreen(plyL, plyR);// display L 1 R 2 player
            while(LPB1&&RPB1==HI);     // wait for player selection button press
            if(LPB1==LO&&RPB1==HI)     // L = 1 plyr, R = 2 plyr
            {
                state = 3;
            }
            else if(LPB1==HI&&RPB1==LO)
            {
                state = 4;
            }
            break;
        case 3:
            
             clearScreen();
             writeMatrix();         // draw left paddle and right wall
             state = 5;
            
            
            break;
           
        case 4:
            col = 0;
            for(row=0; row<8;row++)
            {
                gameArray[row][col]=1;
            }
            col = 15;
            for(row=2; row<5;row++)     // should use paddleMove
            {
                gameArray[row][col]=1;
            }
            writeMatrix();          // draw left paddle and right paddle
            state = 5;
            break;
        case 5:
            
            printDigit(6,8,tres);
            __delay_ms(1000);
            printDigit(6,8,dos);
            __delay_ms(1000);
            printDigit(6,8,uno);
            __delay_ms(1000);
            printDigit(6,8,cero);
            __delay_ms(1000);
            printDigit(6,8,null);
            state = 6;
            break;
        case 6:
             clearScreen();
             GIE = 1;
           
            break;
    }   
    return state;
}