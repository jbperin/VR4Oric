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

unsigned char rollCoord = 0;
#include "tabBorders.c"


unsigned char *baseAdrHigh;
unsigned char *theBaseAdr;
unsigned char *wrtAdr;
unsigned char theColorLeft;
unsigned char theColorRight;
unsigned char X, Y;
unsigned char idxCol, idxLin;
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

            rollCoord       = (abs(rotZ)>4*ANGLE_INCREMENT)?128:0;
            selectTables();
            theBaseAdr      = baseAdrHigh;
            for (idxCol=VIEWPORT_START_COLUMN; idxCol< SCREEN_WIDTH; idxCol+=2) {
                wrtAdr              = theBaseAdr;
                dda1StartValue       = tabLowX[idxCol];
                dda1EndValue         = tabMiddleX[idxCol];
                dda1NbStep           = SCREEN_HEIGHT/2;
                dda1Init();

                dda2StartValue       = tabLowY[idxCol];
                dda2EndValue         = tabMiddleY[idxCol];
                dda2NbStep           = SCREEN_HEIGHT/2;
                dda2Init();

                dda3StartValue       = tabLowX[idxCol+1];
                dda3EndValue         = tabMiddleX[idxCol+1];
                dda3NbStep           = SCREEN_HEIGHT/2;
                dda3Init();

                dda4StartValue       = tabLowY[idxCol+1];
                dda4EndValue         = tabMiddleY[idxCol+1];
                dda4NbStep           = SCREEN_HEIGHT/2;
                dda4Init();

                for (idxLin=0; idxLin< SCREEN_HEIGHT/2; idxLin++) {

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

                dda1StartValue       = tabMiddleX[idxCol];
                dda1EndValue         = tabHighX[idxCol];
                dda1NbStep           = SCREEN_HEIGHT/2;
                dda1Init();

                dda2StartValue       = tabMiddleY[idxCol];
                dda2EndValue         = tabHighY[idxCol];
                dda2NbStep           = SCREEN_HEIGHT/2;
                dda2Init();

                dda3StartValue       = tabMiddleX[idxCol+1];
                dda3EndValue         = tabHighX[idxCol+1];
                dda3NbStep           = SCREEN_HEIGHT/2;
                dda3Init();

                dda4StartValue       = tabMiddleY[idxCol+1];
                dda4EndValue         = tabHighY[idxCol+1];
                dda4NbStep           = SCREEN_HEIGHT/2;
                dda4Init();


                for (idxLin=SCREEN_HEIGHT/2; idxLin< SCREEN_HEIGHT; idxLin++) {

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
