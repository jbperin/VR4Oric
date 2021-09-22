#include <stdio.h>
#include "constants.h"
#include "tabTexelColor.h"

#include "aei1.c"
#include "aei2.c"
#include "aei3.c"
#include "aei4.c"

#define ANGLE_INCREMENT 16
#define abs(x)          (((x)<0)?-(x):(x))

signed char rotZ;
signed char rotX;

#include "tabBorders.c"

unsigned char rollCoord = 0;

unsigned char *baseAdrHigh;
unsigned char *theBaseAdr;
unsigned char *wrtAdr;
unsigned char theColorLeft;
unsigned char theColorRight;
unsigned char X, Y;
unsigned char col, lin;
unsigned char texture_PANO[256*128];

void main (){
    int ii, jj;
    printf ("debut\n");

    rotZ = 7*ANGLE_INCREMENT;
    rotX = -1*ANGLE_INCREMENT;
    
    for (ii =-8; ii <8 ; ii++) {
        for (jj = -3; jj <4; jj++) {

            printf ("ii = %d, jj = %d\n", ii, jj);

            rotZ = ii*ANGLE_INCREMENT;
            rotX = jj*ANGLE_INCREMENT;

            selectTables();

            rollCoord       = (abs(rotZ)>4*ANGLE_INCREMENT);
            selectTables();
            theBaseAdr      = baseAdrHigh;
            for (col=VIEWPORT_START_COLUMN; col< SCREEN_WIDTH; col+=2) {
                wrtAdr              = theBaseAdr;
                dda1StartValue       = tabLowX[col];
                dda1EndValue         = tabMiddleX[col];
                dda1NbStep           = SCREEN_HEIGHT/2;
                dda1Init();

                dda2StartValue       = tabLowY[col];
                dda2EndValue         = tabMiddleY[col];
                dda2NbStep           = SCREEN_HEIGHT/2;
                dda2Init();

                dda3StartValue       = tabLowX[col+1];
                dda3EndValue         = tabMiddleX[col+1];
                dda3NbStep           = SCREEN_HEIGHT/2;
                dda3Init();

                dda4StartValue       = tabLowY[col+1];
                dda4EndValue         = tabMiddleY[col+1];
                dda4NbStep           = SCREEN_HEIGHT/2;
                dda4Init();

                for (lin=0; lin< SCREEN_HEIGHT/2; lin++) {

                    X   = dda1CurrentValue;
                    if (rollCoord) X+=128;
                    Y   = dda2CurrentValue;
                    theColorLeft = texture_PANO[X*IMAGE_HEIGHT+Y];

                    X   = dda3CurrentValue;
                    if (rollCoord) X+=128;
                    Y   = dda4CurrentValue;
                    theColorRight = texture_PANO[X*IMAGE_HEIGHT+Y];


                    // *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    // *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;

                    (*dda1StepFunction)();
                    (*dda2StepFunction)();
                    (*dda3StepFunction)();
                    (*dda4StepFunction)();

                }

                dda1StartValue       = tabMiddleX[col];
                dda1EndValue         = tabHighX[col];
                dda1NbStep           = SCREEN_HEIGHT/2;
                dda1Init();

                dda2StartValue       = tabMiddleY[col];
                dda2EndValue         = tabHighY[col];
                dda2NbStep           = SCREEN_HEIGHT/2;
                dda2Init();

                dda3StartValue       = tabMiddleX[col+1];
                dda3EndValue         = tabHighX[col+1];
                dda3NbStep           = SCREEN_HEIGHT/2;
                dda3Init();

                dda4StartValue       = tabMiddleY[col+1];
                dda4EndValue         = tabHighY[col+1];
                dda4NbStep           = SCREEN_HEIGHT/2;
                dda4Init();


                for (lin=SCREEN_HEIGHT/2; lin< SCREEN_HEIGHT; lin++) {

                    X   = dda1CurrentValue;
                    if (rollCoord) X+=128;
                    Y   = dda2CurrentValue;
                    theColorLeft = texture_PANO[X*IMAGE_HEIGHT+Y];

                    X   = dda3CurrentValue;
                    if (rollCoord) X+=128;
                    Y   = dda4CurrentValue;
                    theColorRight = texture_PANO[X*IMAGE_HEIGHT+Y];

                    // *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    // *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;

                    (*dda1StepFunction)();
                    (*dda2StepFunction)();
                    (*dda3StepFunction)();
                    (*dda4StepFunction)();

                }
                theBaseAdr += 1;
            }


        }

    }
    printf ("fin\n");
}
