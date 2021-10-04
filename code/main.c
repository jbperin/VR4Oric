#include <lib.h>

#include "loader_api.h"
#include "config.h"
#include "texel.c"

extern unsigned char texture_PANO[];
extern unsigned char borderTables[];

#include "keyboard_c.c"
#include "aei1.c"
#include "aei2.c"
#include "aei3.c"
#include "aei4.c"

#define abs(x)          (((x)<0)?-(x):(x))
#define ANGLE_INCREMENT                 16

#define CHANGE_INK_TO_BLACK             0
#define CHANGE_INK_TO_RED	            1		
#define CHANGE_INK_TO_GREEN	            2		
#define CHANGE_INK_TO_BLUE	            4		
#define CHANGE_PAPER_TO_WHITE	        23



signed char rotX, rotZ;
unsigned char rollCoord = 0;

#include "tabBorders.c"


unsigned char col, lin;

unsigned char theX, theY;
unsigned char *theBaseAdr;
unsigned char *wrtAdr;
unsigned char theColorLeft;
unsigned char theColorRight;

char IsHires=1;
unsigned char running ;
unsigned char refreshNeeded = 1;
unsigned char scene_number = 0;

// signed char latitude, longitude;

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
    if (c == KEY_DOWN ) {
        if (rotX < 2*ANGLE_INCREMENT){
            rotX += ANGLE_INCREMENT;
            refreshNeeded   = 1;
        }
    } else if (c == KEY_UP) {
        if (rotX > -2*ANGLE_INCREMENT){
            rotX -= ANGLE_INCREMENT;
            refreshNeeded   = 1;
        }
    } else if (c == KEY_LEFT) {
        if (rotZ < 7*ANGLE_INCREMENT){
            rotZ += ANGLE_INCREMENT;
        }else{
            rotZ = -8*ANGLE_INCREMENT;
        }
        refreshNeeded   = 1;
    } else if (c == KEY_RIGHT) {
        if (rotZ > -8*ANGLE_INCREMENT){
            rotZ -= ANGLE_INCREMENT;
        } else {
            rotZ = 7*ANGLE_INCREMENT;
        }
        refreshNeeded   = 1;
    } else if (c == KEY_SPACE) {
        if ((scene_number == 0) && (rotZ==0x00) && (rotX==0x00)){
            scene_number            = 1;
            LoadFileAt(LOADER_PANO_02,texture_PANO);
            refreshNeeded           = 1;
        } else if ((scene_number == 1) && ((unsigned char)rotZ==0x80) && (rotX==0x00)) { 
            scene_number            = 0;
            LoadFileAt(LOADER_PANO_01,texture_PANO);
            refreshNeeded           = 1;
        }
    } else if (c == KEY_ESCAPE) {
            running = 0;
    }
    rollCoord       = (abs(rotZ)>4*ANGLE_INCREMENT)?1:0;
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

#define DEFAULT_BASE_ADRESS (HIRES_SCREEN_ADDRESS + 40*((VIEWPORT_START_LINE<<1) + VIEWPORT_START_LINE) + (VIEWPORT_START_COLUMN>>1))


void main()
{


    rotX = 0; rotZ = 0x30;
    LoadFileAt(LOADER_BTABLES, borderTables);
    LoadFileAt(LOADER_PANO_01, texture_PANO);
    scene_number            = 0;
	SwitchToHires();
	running = 1;
    kernelInit();

    // OPTIME baseAdrHigh     = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(VIEWPORT_START_LINE<<1) + VIEWPORT_START_LINE] + (VIEWPORT_START_COLUMN>>1));
    // baseAdrHigh     = (unsigned char *)(DEFAULT_BASE_ADRESS);
    // baseAdrLow      = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[((VIEWPORT_START_LINE+SCREEN_HEIGHT/2)<<1) + (VIEWPORT_START_LINE+SCREEN_HEIGHT/2)] + (VIEWPORT_START_COLUMN>>1));

    while (running) {

        lsys();
        
        if (refreshNeeded) {
            // clearViewport();
            rollCoord       = (abs(rotZ)>4*ANGLE_INCREMENT);
            selectTables();
            theBaseAdr      = (unsigned char *)(DEFAULT_BASE_ADRESS);
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

                    // computeEquiRect();
                    // colorSquare(lin, col, texture_PANO[X*IMAGE_HEIGHT+Y]);

                    theX   = dda1CurrentValue;
                    if (rollCoord) theX+=128;
                    theY   = dda2CurrentValue;
                    theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];

                    theX   = dda3CurrentValue;
                    if (rollCoord) theX+=128;
                    theY   = dda4CurrentValue;
                    theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];

                    // adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));

                    *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
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

                    // computeEquiRect();
                    // colorSquare(lin, col, texture_PANO[X*IMAGE_HEIGHT+Y]);

                    theX   = dda1CurrentValue;
                    if (rollCoord) theX+=128;
                    theY   = dda2CurrentValue;
                    theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];

                    theX   = dda3CurrentValue;
                    if (rollCoord) theX+=128;
                    theY   = dda4CurrentValue;
                    theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];

                    // theAdrHigh = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));
                    *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
                    wrtAdr += NEXT_SCANLINE_INCREMENT;
                    (*dda1StepFunction)();
                    (*dda2StepFunction)();
                    (*dda3StepFunction)();
                    (*dda4StepFunction)();
                }
                theBaseAdr += 1;
            }
            refreshNeeded = 0;
        }
	}
}
