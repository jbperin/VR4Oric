

#include <lib.h>

#include "loader_api.h"
#include "config.h"
#include "texel.c"

//#include "image.c"
extern unsigned char texture_PANO[];
// #include "tabEquiRect.c"
// extern unsigned char tabLong2Col[];
// extern unsigned char tabLat2Lin[];
// extern signed char tabAtanCol[];
// extern signed char tabAtanLin[];

#include "keyboard_c.c"
#include "aei1.c"
#include "aei2.c"
#include "aei3.c"
#include "aei4.c"
#include "tabBorders.c"

#define CHANGE_INK_TO_BLACK             0
#define CHANGE_INK_TO_RED	            1		
#define CHANGE_INK_TO_GREEN	            2		
#define CHANGE_INK_TO_BLUE	            4		
#define CHANGE_PAPER_TO_WHITE	        23
#define abs(x)          (((x)<0)?-(x):(x))

char IsHires=1;
unsigned char col, lin;
signed char latitude, longitude;
signed char rotX, rotZ;
unsigned char X, Y;
unsigned char running ;
unsigned char refreshNeeded = 1;

// void computeEquiRect(){
//             latitude = tabAtanLin[lin] + rotX;
//             longitude = tabAtanCol[col] + rotZ;
//             if ((abs(latitude) > 64)) {
//                 longitude = (longitude + 64);
//                 latitude = -latitude + 128;
//             }
//             X = tabLong2Col[(unsigned char)longitude];
//             Y = tabLat2Lin[(unsigned char)latitude];
// }

#define ANGLE_INCREMENT 16

void prepareRGB(){
    int ii;

    // parcours de lignes de 3 en 3
    for (ii=0; ii < (TEXT_SCREEN_HEIGHT - NB_LESS_LINES_4_COLOR)*8;  ii+=3){
        *((char*)(HIRES_SCREEN_ADDRESS+((ii)*NEXT_SCANLINE_INCREMENT)))=CHANGE_INK_TO_RED;
        *((char*)(HIRES_SCREEN_ADDRESS+((ii+1)*NEXT_SCANLINE_INCREMENT)))=CHANGE_INK_TO_GREEN;
        *((char*)(HIRES_SCREEN_ADDRESS+((ii+2)*NEXT_SCANLINE_INCREMENT)))=CHANGE_INK_TO_BLUE;
    }
}


void SwitchToHires()
{
	if (!IsHires)
	{
		// If not in HIRES; we need to switch from TEXT to HIRES
		memcpy((unsigned char*)0x9800,(unsigned char*)0xb400,0xbb80-0xb400);		// Move the charsets from TOP to BOTTOM
		memset((unsigned char*)0xa000,0,40*200);									// Clear the entire HIRES area with black ink
		*((char*)0xbfdf)=30;														// 50hz Graphics attribute

		memset((unsigned char*)0xa000,64,40*200);									// Fill the entire HIRES area with neutral 64 value
	}
	IsHires=1;
    // memset((unsigned char*)0xbf40,0x20,40*4);
    prepareRGB();	
    // *((char*)0xbf40)=0x17;	
    // *((char*)0xbf41)=0x00;	
    // *((char*)0xbf68)=0x17;	
    // *((char*)0xbf69)=0x00;	
    // *((char*)0xbf90)=0x17;	
    // *((char*)0xbf91)=0x00;	
    // *((char*)0xbfb8)=0x17;	
    // *((char*)0xbfb9)=0x00;	
}


void keyPressed(unsigned char c){
	// printf ("kp: %x, ", c);
    if (c == keyForward) {
            rotX += ANGLE_INCREMENT;
            refreshNeeded   = 1;
    } else if (c == keyBackward) {
            rotX -= ANGLE_INCREMENT;
            refreshNeeded   = 1;
    } else if (c == keyTurnLeft) {
            rotZ -= ANGLE_INCREMENT;
            refreshNeeded   = 1;
    } else if (c == keyTurnRight) {
            rotZ += ANGLE_INCREMENT;
            refreshNeeded   = 1;
    } else if (c == keyStraffeRight) {
            LoadFileAt(LOADER_PANO_02,texture_PANO);
            refreshNeeded           = 1;
    } else if (c == keyStraffeLeft) {
            refreshNeeded           = 1;
    } else if (c == keyQuit) {
            running = 0;
    }

}

void keyReleased(unsigned char c){
	// printf ("kr: %x, ", c);
}

void lsys(){
	unsigned char c;
	while (nbE_keybuf != 0) {
		if ((c=get_keyevent()) & 0x80){
			keyReleased (c & 0x7F);
		} else {
			keyPressed (c);
		}
	}
}

void main()
{

    unsigned char *lowX;
    unsigned char *middleX;
    unsigned char *highX;
    unsigned char *lowY;
    unsigned char *middleY;
    unsigned char *highY;

    unsigned char *adr;
    unsigned char theColorLeft;
    unsigned char theColorRight;

    LoadFileAt(LOADER_PANO_01, texture_PANO);
	SwitchToHires();
	running = 1;
    kernelInit();

    lowX            = tabLowX_p0_p0;
    middleX         = tabMiddleX_p0_p0;
    highX           = tabHighX_p0_p0;
    lowY            = tabLowY_p0_p0;
    middleY         = tabMiddleY_p0_p0;
    highY           = tabHighY_p0_p0;

    while (running) {

        lsys();
        
        if (refreshNeeded) {
            clearViewport();
            for (col=2; col< SCREEN_WIDTH; col+=2) {
                
                dda1StartValue       = lowX[col];
                dda1EndValue         = middleX[col];
                dda1NbStep           = SCREEN_HEIGHT/2;
                dda1Init();

                dda2StartValue       = lowY[col];
                dda2EndValue         = middleY[col];
                dda2NbStep           = SCREEN_HEIGHT/2;
                dda2Init();

                dda3StartValue       = lowX[col+1];
                dda3EndValue         = middleX[col+1];
                dda3NbStep           = SCREEN_HEIGHT/2;
                dda3Init();

                dda4StartValue       = lowY[col+1];
                dda4EndValue         = middleY[col+1];
                dda4NbStep           = SCREEN_HEIGHT/2;
                dda4Init();

                for (lin=0; lin< SCREEN_HEIGHT/2; lin++) {

                    // computeEquiRect();
                    // colorSquare(lin, col, texture_PANO[X*IMAGE_HEIGHT+Y]);

                    X   = dda1CurrentValue;
                    Y   = dda2CurrentValue;
                    theColorLeft = texture_PANO[X*IMAGE_HEIGHT+Y];

                    X   = dda3CurrentValue;
                    Y   = dda4CurrentValue;
                    theColorRight = texture_PANO[X*IMAGE_HEIGHT+Y];

                    adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));

                    *adr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
                    adr += NEXT_SCANLINE_INCREMENT;
                    *adr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
                    adr += NEXT_SCANLINE_INCREMENT;
                    *adr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];

                    // if ((col&0x01) != 0){
                    //     *adr |= tabRightRed[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabRightGreen[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabRightBlue[theColorLeft];
                    // } else {
                    //     *adr |= tabLeftRed[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabLeftGreen[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabLeftBlue[theColorLeft];
                    // }

                    (*dda1StepFunction)();
                    (*dda2StepFunction)();
                    (*dda3StepFunction)();
                    (*dda4StepFunction)();

                }

                dda1StartValue       = middleX[col];
                dda1EndValue         = highX[col];
                dda1NbStep           = SCREEN_HEIGHT/2;
                dda1Init();

                dda2StartValue       = middleY[col];
                dda2EndValue         = highY[col];
                dda2NbStep           = SCREEN_HEIGHT/2;
                dda2Init();

                dda3StartValue       = middleX[col+1];
                dda3EndValue         = highX[col+1];
                dda3NbStep           = SCREEN_HEIGHT/2;
                dda3Init();

                dda4StartValue       = middleY[col+1];
                dda4EndValue         = highY[col+1];
                dda4NbStep           = SCREEN_HEIGHT/2;
                dda4Init();


                for (lin=SCREEN_HEIGHT/2; lin< SCREEN_HEIGHT; lin++) {

                    // computeEquiRect();
                    // colorSquare(lin, col, texture_PANO[X*IMAGE_HEIGHT+Y]);

                    X   = dda1CurrentValue;
                    Y   = dda2CurrentValue;
                    theColorLeft = texture_PANO[X*IMAGE_HEIGHT+Y];

                    X   = dda3CurrentValue;
                    Y   = dda4CurrentValue;
                    theColorRight = texture_PANO[X*IMAGE_HEIGHT+Y];

                    adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));
                    *adr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
                    adr += NEXT_SCANLINE_INCREMENT;
                    *adr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
                    adr += NEXT_SCANLINE_INCREMENT;
                    *adr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
                    // if ((col&0x01) != 0){
                    //     *adr |= tabRightRed[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabRightGreen[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabRightBlue[theColorLeft];
                    // } else {
                    //     *adr |= tabLeftRed[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabLeftGreen[theColorLeft];
                    //     adr += NEXT_SCANLINE_INCREMENT;
                    //     *adr |= tabLeftBlue[theColorLeft];
                    // }

                    (*dda1StepFunction)();
                    (*dda2StepFunction)();
                    (*dda3StepFunction)();
                    (*dda4StepFunction)();

                }
            }

            refreshNeeded = 0;
        }
	}
}
