#include <lib.h>

#include "loader_api.h"
#include "config.h"
#include "texel.c"

extern unsigned char texture_PANO[];
extern unsigned char borderTables[];
extern unsigned char adrTextureHigh[];
extern unsigned char adrTextureLow[];
extern unsigned char diffimg[]; // 8672

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
// can be 0 when no rollover occurs on X coordinate of equirectangular image
// or 128 when a rollover occurs on X coordinate

#include "tabBorders.c"


extern unsigned char idxCol, idxLin;

extern unsigned char theX, theY;
extern unsigned char *theBaseAdr;
extern unsigned char *wrtAdr;
extern unsigned char theColorLeft;
extern unsigned char theColorRight;

char IsHires=0;
unsigned char running ;
unsigned char waiting ;
unsigned char refreshNeeded = 1;

unsigned char scene_number = 0;
unsigned char has_key   =   0;

unsigned char diff_index;
int nbval, diffidx;
void apply_diff(){

    
    nbval = diffimg[1]*256 + diffimg[2]; // 508 ; //(int)(((int)diffimg[1])<<8 + diffimg[2]);
    for (diffidx=0; diffidx< nbval; diffidx++){
        theX = diffimg[(diffidx*3)+3];
        theY = diffimg[(diffidx*3)+3+1];
        {asm(":debappdiff:");}
        texture_PANO[theX * IMAGE_HEIGHT + theY] = diffimg[(diffidx*3)+3+2];
    }
}



void prepareRGB(){
    int ii;

    // parcours de lignes de 3 en 3
    for (ii=0; ii < (TEXT_SCREEN_HEIGHT - NB_LESS_LINES_4_COLOR)*8;  ii+=3){
        *((char*)(HIRES_SCREEN_ADDRESS+((ii)*NEXT_SCANLINE_INCREMENT)))=CHANGE_INK_TO_RED;
        *((char*)(HIRES_SCREEN_ADDRESS+((ii+1)*NEXT_SCANLINE_INCREMENT)))=CHANGE_INK_TO_GREEN;
        *((char*)(HIRES_SCREEN_ADDRESS+((ii+2)*NEXT_SCANLINE_INCREMENT)))=CHANGE_INK_TO_BLUE;
    }
}


void SwitchToText()
{
    // LoadFileAt(LOADER_FONT_6x8, 0xb500);
	if (IsHires)
	{
		// If not in TEXT; we need to switch from HIRES to TEXT
        // Clear the entire HIRES area with black ink
		memset((unsigned char*)0xa000,0,40*200);	
		// Move the charsets from BOTTOM to TOP
        memcpy((unsigned char*)0xb400,(unsigned char*)0x9800,0xbb80-0xb400);		
        // Fill the entire TEXT area with spaces
		memset((unsigned char*)0xbb80,32,40*25);	
	}
    // 50hz Text attribute
    *((char*)0xbfdf) = 26;														
    *((char*)0xbbd0) = 0x10;
    *((char*)0xbbd1) = 0x07;
    *((char*)0xbbf8) = 0x10;
    *((char*)0xbbf9) = 0x07;
    *((char*)0xbf68) = 0x10;
    *((char*)0xbf69) = 0x07;
    *((char*)0xbf90) = 0x10;
    *((char*)0xbf91) = 0x07;
	IsHires=0;
}
void SwitchToHires()
{
	if (!IsHires)
	{
		// If not in HIRES; we need to switch from TEXT to HIRES
        // Move the charsets from TOP to BOTTOM
		memcpy((unsigned char*)0x9800,(unsigned char*)0xb400,0xbb80-0xb400);
        // Clear the entire HIRES area with black ink
		memset((unsigned char*)0xa000,0,40*200);

		memset((unsigned char*)0xa000,64,40*200);									// Fill the entire HIRES area with neutral 64 value
	}
    // 50hz Graphics attribute
    *((char*)0xbfdf)=30;
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
    theX = c;
    waiting = 0;
    // {asm("lda _theX: breakkey:");}
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
    } else if (c == KEY_G) {
        if ((scene_number == 0) ){
            has_key = 1;
            diff_index = 0;
            apply_diff();
            refreshNeeded   = 1;
        } 
    } else if (c == KEY_H) {
        SwitchToText();
        AdvancedPrint(2, 2, "Colorfull 360 degrees 3D for Oric");
        AdvancedPrint(2, 3, "Tech Demo by Jean-Baptiste PERIN");
        AdvancedPrint(2, 26, "Press a key to game");
        running = 0;
//        refreshNeeded   = 1;
    } else if (c == KEY_RIGHT) {
        if (rotZ > -8*ANGLE_INCREMENT){
            rotZ -= ANGLE_INCREMENT;
        } else {
            rotZ = 7*ANGLE_INCREMENT;
        }
        refreshNeeded   = 1;
    } else if (c == KEY_SPACE) {
        if ((scene_number == 0) && (has_key == 0) && (rotZ==0x00) && (rotX==0x00)){
            AdvancedPrint(2, 26, "You need a key yo open this door.");
        } else if ((scene_number == 0) && (has_key != 0) && (rotZ==0x00) && (rotX==0x00)){
            scene_number            = 1;
            LoadFileAt(LOADER_PANO_02,texture_PANO);
            refreshNeeded           = 1;
        } else if ((scene_number == 1) && ((unsigned char)rotZ==0x80) && (rotX==0x00)) { 
            scene_number            = 0;
            LoadFileAt(LOADER_PANO_01,texture_PANO);
            LoadFileAt(LOADER_DIFFIMG, diffimg);
            if (has_key != 0) {
                diff_index = 0;
                apply_diff();
            }
            refreshNeeded           = 1;
        }
    } else if (c == KEY_ESCAPE) {
            running = 0;
    }
    rollCoord       = (abs(rotZ)>4*ANGLE_INCREMENT)?128:0;
}

void keyReleased(unsigned char c){
	// printf ("kr: %x, ", c);
    //waiting = 0;
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

void project2ScreenASM ();


#include "render_c.c"

char message[]="coucou\0";
void main()
{
    int ii = 0;

    LoadFileAt(LOADER_FONT_6x8, 0xb500);

    for (ii=0; ii < 256; ii++) {
        adrTextureHigh[ii] = (unsigned char)((((int)texture_PANO) + 128*ii)>>8);
        adrTextureLow[ii] = (unsigned char)(((((int)texture_PANO) + 128*ii) & 0x00FF));
    }
    LoadFileAt(LOADER_BTABLES, borderTables);



    


    kernelInit();


    LoadFileAt(LOADER_PANO_01, texture_PANO);
    LoadFileAt(LOADER_DIFFIMG, diffimg);
    rotX = 0; rotZ = 0xC0;
    scene_number            = 0;
    

    while (1) {
        SwitchToText();
        AdvancedPrint(2, 2, "Colorfull 360 degrees 3D for Oric");
        AdvancedPrint(2, 3, "Tech Demo by Jean-Baptiste PERIN");
        AdvancedPrint(2, 26, "Press a key to game");
        waiting = 1;
        while (waiting) {

            lsys();
        }
        refreshNeeded = 1;
        SwitchToHires();
        running = 1;


        
        while (running) {

            lsys();
            
            if (refreshNeeded) {
                // clearViewport();
                // rollCoord       = (abs(rotZ)>4*ANGLE_INCREMENT);
                selectTables();

#ifdef  __USE_PURE_ASM_RENDER__               
                project2ScreenPureASM();
#else 
#ifdef  __USE_C_ASM_RENDER__
                project2ScreenCASM ();
#else
#ifdef  __USE_PURE_C_RENDER__
                project2Screen ();
#endif
#endif
#endif
                // project2ScreenOPTIM ();
                // 
#endif
                AdvancedPrint(2, 26, "                                  ");

                if ((scene_number == 0))
                {                
                    if ((rotZ <= 0x60 ) && (rotZ >= 0x50) 
                        && (rotX >= 0x10) && (rotX <= 0x20)
                        && (! has_key)) {
                        AdvancedPrint(2, 26, "You can [G]rab this key");
                    } else if ((rotZ == 0x00 ) && (rotX == 0x00) ) {
                        AdvancedPrint(2, 26, "There's a door here ..");
                    }

                }
                if ((scene_number == 1)){
                    {asm(":break01:")}
                    if ((rotZ == ((signed char)0x80) ) && (rotX == 0x00) ) {
                        AdvancedPrint(2, 26, "There's a door here ..");
                    }
                }



                refreshNeeded = 0;
            }
        }


    }
#ifdef __DONT_RUN__
#endif // __DONT_RUN__    
}




// void project2ScreenASM () {
//     theBaseAdr      = (unsigned char *)(DEFAULT_BASE_ADRESS);
//     for (idxCol=VIEWPORT_START_COLUMN; idxCol< SCREEN_WIDTH; idxCol+=2) {
//         // wrtAdr              = theBaseAdr;
//         asm ("lda _theBaseAdr: sta _wrtAdr: lda _theBaseAdr+1: sta _wrtAdr+1:");

//         // dda1StartValue       = tabLowX[idxCol];
//         // dda1EndValue         = tabMiddleX[idxCol];
//         asm ("ldy _idxCol:"
//             " lda _tabLowX, y: sta _dda1StartValue: sta _dda1CurrentValue: lda _tabMiddleX, y: sta _dda1EndValue:"
//             " lda _tabLowY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabMiddleY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:"
//             "iny:"
//             " lda _tabLowX, y: sta _dda3StartValue: sta _dda3CurrentValue: lda _tabMiddleX, y: sta _dda3EndValue:"
//             " lda _tabLowY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabMiddleY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:"
//             );
//         // dda1NbStep           = SCREEN_HEIGHT/2;
//         asm ("lda #32:"
//             "sta _dda1NbStep:"
//             "sta _dda2NbStep: sta _dda2CurrentError:"
//             "sta _dda3NbStep:"
//             "sta _dda4NbStep: sta _dda4CurrentError:"
//         ); // FIXME: replace 32 by SCREEN_HEIGHT/2

//         // dda1CurrentValue         = dda1StartValue;

//         if (dda1EndValue > dda1StartValue) {
//             dda1NbVal                = dda1EndValue-dda1StartValue;
//             dda1Increment            = 1;
//         } else {
//             dda1NbVal                = dda1StartValue-dda1EndValue;
//             dda1Increment            = -1;
//         }

//         if          (dda1NbVal > dda1NbStep) {
//             dda1CurrentError     = dda1NbVal;
//             dda1StepFunction     = &dda1Step1;
//         } else if   (dda1NbVal < dda1NbStep) {
//             dda1CurrentError     = dda1NbStep;
//             dda1StepFunction     = &dda1Step2;
//         } else {
//             dda1CurrentError     = dda1EndValue;
//             dda1StepFunction     = &dda1Step0;
//         }
//         // dda2StartValue       = tabLowY[idxCol];
//         // dda2EndValue         = tabMiddleY[idxCol];
//         // dda2NbStep           = SCREEN_HEIGHT/2;

//         // dda2CurrentValue         = dda2StartValue;
//         // dda2NbVal                = dda2EndValue-dda2StartValue;
//         // dda2CurrentError     = dda2NbStep;
//         // dda2StepFunction     = &dda2Step2;


//         // dda3StartValue       = tabLowX[idxCol+1];
//         // dda3EndValue         = tabMiddleX[idxCol+1];
//         // dda3NbStep           = SCREEN_HEIGHT/2;
//         // dda3CurrentValue         = dda3StartValue;

//         if (dda3EndValue > dda3StartValue) {
//             dda3NbVal                = dda3EndValue-dda3StartValue;
//             dda3Increment            = 1;
//         } else {
//             dda3NbVal                = dda3StartValue-dda3EndValue;
//             dda3Increment            = -1;
//         }

//         if          (dda3NbVal > dda3NbStep) {
//             dda3CurrentError     = dda3NbVal;
//             dda3StepFunction     = &dda3Step1;
//         } else if   (dda3NbVal < dda3NbStep) {
//             dda3CurrentError     = dda3NbStep;
//             dda3StepFunction     = &dda3Step2;
//         } else {
//             dda3CurrentError     = dda3EndValue;
//             dda3StepFunction     = &dda3Step0;
//         }

//         // dda4StartValue       = tabLowY[idxCol+1];
//         // dda4EndValue         = tabMiddleY[idxCol+1];
//         // dda4NbStep           = SCREEN_HEIGHT/2;
//         // dda4Init();

//         // dda4CurrentValue         = dda4StartValue;
//         // dda4NbVal                = dda4EndValue-dda4StartValue;
//         // dda4CurrentError     = dda4NbStep;
//         // dda4StepFunction     = &dda4Step2;


//         for (idxLin=0; idxLin< SCREEN_HEIGHT/2; idxLin+=2) {

//             // theX   = dda1CurrentValue + rollCoord;
//             // theY   = dda2CurrentValue;
//             asm (
//                 "lda _dda1CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda2CurrentValue: sta _theY:"
//             );
            
//             // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorLeft:"
//             );

//             // theX   = dda3CurrentValue + rollCoord;
//             // theY   = dda4CurrentValue;
//             asm (
//                 "lda _dda3CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda4CurrentValue: sta _theY:"
//             );

//             // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorRight:"
//             );

//             // adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));
//             asm (
//                 "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #0: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #40: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #80: sta (_wrtAdr),y:"
//                 // "lda _wrtAdr: clc: adc #120: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):"
//             );
//             // *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;

//             (*dda1StepFunction)();
//             dda2CurrentError         -= dda2NbVal;
//             if ((dda2CurrentError<<1) < dda2NbStep) {
//                 dda2CurrentError     += dda2NbStep;
//                 dda2CurrentValue     ++;
//             }
//             (*dda3StepFunction)();
//             dda4CurrentError         -= dda4NbVal; 
//             if ((dda4CurrentError<<1) < dda4NbStep) {
//                 dda4CurrentError     += dda4NbStep;
//                 dda4CurrentValue     ++;
//             }


//             // theX   = dda1CurrentValue + rollCoord;
//             // theY   = dda2CurrentValue;
//             asm (
//                 "lda _dda1CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda2CurrentValue: sta _theY:"
//             );
            
//             // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorLeft:"
//             );

//             // theX   = dda3CurrentValue + rollCoord;
//             // theY   = dda4CurrentValue;
//             asm (
//                 "lda _dda3CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda4CurrentValue: sta _theY:"
//             );

//             // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorRight:"
//             );

//             // adr = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));
//             asm (
//                 "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #120: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #160: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #200: sta (_wrtAdr),y:"
//                 "lda _wrtAdr: clc: adc #240: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):"
//             );
//             // *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;

//             (*dda1StepFunction)();
//             dda2CurrentError         -= dda2NbVal;
//             if ((dda2CurrentError<<1) < dda2NbStep) {
//                 dda2CurrentError     += dda2NbStep;
//                 dda2CurrentValue     ++;
//             }
//             (*dda3StepFunction)();
//             dda4CurrentError         -= dda4NbVal; 
//             if ((dda4CurrentError<<1) < dda4NbStep) {
//                 dda4CurrentError     += dda4NbStep;
//                 dda4CurrentValue     ++;
//             }

//         }

//         asm ("ldy _idxCol:"
//             " lda _tabMiddleX, y: sta _dda1StartValue: lda _tabHighX, y: sta _dda1EndValue:"
//             " lda _tabMiddleY, y: sta _dda2StartValue: lda _tabHighY, y: sta _dda2EndValue:"
//             // " lda _tabMiddleY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabHighY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:"
//             "iny:"
//             " lda _tabMiddleX, y: sta _dda3StartValue: lda _tabHighX, y: sta _dda3EndValue:"
//             " lda _tabMiddleY, y: sta _dda4StartValue: lda _tabHighY, y: sta _dda4EndValue:"
//             // " lda _tabMiddleY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabHighY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:"
//             );
//         // asm ("ldy _idxCol:"
//         //     " lda _tabMiddleX, y: sta _dda1StartValue: lda _tabHighX, y: sta _dda1EndValue:"
//         //     " lda _tabMiddleY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabHighY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:"
//         //     "iny:"
//         //     " lda _tabMiddleX, y: sta _dda3StartValue: lda _tabHighX, y: sta _dda3EndValue:"
//         //     " lda _tabMiddleY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabHighY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:"
//         //     );

//         asm ("lda #32:"
//             "sta _dda1NbStep:"
//             "sta _dda2NbStep: sta _dda2CurrentError:"
//             // "sta _dda2NbStep:"
//             "sta _dda3NbStep:"
//             // "sta _dda4NbStep:"
//             "sta _dda4NbStep: sta _dda4CurrentError:"
//         ); // FIXME: replace 32 by SCREEN_HEIGHT/2


//         // dda1StartValue       = tabMiddleX[idxCol];
//         // dda1EndValue         = tabHighX[idxCol];
//         // dda1NbStep           = SCREEN_HEIGHT/2;
//         dda1CurrentValue         = dda1StartValue;

//         if (dda1EndValue > dda1StartValue) {
//             dda1NbVal                = dda1EndValue-dda1StartValue;
//             dda1Increment            = 1;
//         } else {
//             dda1NbVal                = dda1StartValue-dda1EndValue;
//             dda1Increment            = -1;
//         }

//         if          (dda1NbVal > dda1NbStep) {
//             dda1CurrentError     = dda1NbVal;
//             dda1StepFunction     = &dda1Step1;
//         } else if   (dda1NbVal < dda1NbStep) {
//             dda1CurrentError     = dda1NbStep;
//             dda1StepFunction     = &dda1Step2;
//         } else {
//             dda1CurrentError     = dda1EndValue;
//             dda1StepFunction     = &dda1Step0;
//         }

//         // dda2StartValue       = tabMiddleY[idxCol];
//         // dda2EndValue         = tabHighY[idxCol];
//         // dda2NbStep           = SCREEN_HEIGHT/2;
//         // dda2Init();

//         dda2CurrentValue         = dda2StartValue;
//         dda2NbVal                = dda2EndValue-dda2StartValue;
//         // dda2CurrentError     = dda2NbStep;
//         // dda2StepFunction     = &dda2Step2;

//         // dda3StartValue       = tabMiddleX[idxCol+1];
//         // dda3EndValue         = tabHighX[idxCol+1];
//         // dda3NbStep           = SCREEN_HEIGHT/2;
//         dda3CurrentValue         = dda3StartValue;

//         if (dda3EndValue > dda3StartValue) {
//             dda3NbVal                = dda3EndValue-dda3StartValue;
//             dda3Increment            = 1;
//         } else {
//             dda3NbVal                = dda3StartValue-dda3EndValue;
//             dda3Increment            = -1;
//         }

//         if          (dda3NbVal > dda3NbStep) {
//             dda3CurrentError     = dda3NbVal;
//             dda3StepFunction     = &dda3Step1;
//         } else if   (dda3NbVal < dda3NbStep) {
//             dda3CurrentError     = dda3NbStep;
//             dda3StepFunction     = &dda3Step2;
//         } else {
//             dda3CurrentError     = dda3EndValue;
//             dda3StepFunction     = &dda3Step0;
//         }
//         // dda4StartValue       = tabMiddleY[idxCol+1];
//         // dda4EndValue         = tabHighY[idxCol+1];
//         // dda4NbStep           = SCREEN_HEIGHT/2;
//         // dda4Init();

//         dda4CurrentValue         = dda4StartValue;
//         dda4NbVal                = dda4EndValue-dda4StartValue;
//         // dda4CurrentError     = dda4NbStep;
//         // dda4StepFunction     = &dda4Step2;

//         for (idxLin=SCREEN_HEIGHT/2; idxLin< SCREEN_HEIGHT; idxLin+=2) {

//             // theX   = dda1CurrentValu + rollCoord;
//             // theY   = dda2CurrentValue;
//             asm (
//                 "lda _dda1CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda2CurrentValue: sta _theY:"
//             );

//             // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorLeft:"
//             );

//             // theX   = dda3CurrentValue + rollCoord;
//             // theY   = dda4CurrentValue;
//             asm (
//                 "lda _dda3CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda4CurrentValue: sta _theY:"
//             );

//             // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorRight:"
//             );

//             // theAdrHigh = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));
//             // *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             asm (
//                 "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #0: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #40: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #80: sta (_wrtAdr),y:"
//                 // "lda _wrtAdr: clc: adc #120: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):"
//             );

//             (*dda1StepFunction)();
//             dda2Step2();
//             (*dda3StepFunction)();
//             dda4Step2();

//             // theX   = dda1CurrentValu + rollCoord;
//             // theY   = dda2CurrentValue;
//             asm (
//                 "lda _dda1CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda2CurrentValue: sta _theY:"
//             );

//             // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorLeft:"
//             );

//             // theX   = dda3CurrentValue + rollCoord;
//             // theY   = dda4CurrentValue;
//             asm (
//                 "lda _dda3CurrentValue: adc _rollCoord: sta _theX:"
//                 "lda _dda4CurrentValue: sta _theY:"
//             );

//             // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
//             asm (
//                 "ldy _theX:"
//                 "lda _adrTextureLow,y:"
//                 "sta _myTmp:"
//                 "lda _adrTextureHigh,y:"
//                 "sta _myTmp+1:"
//                 "ldy _theY:"
//                 "lda (_myTmp),y:"
//                 "sta _theColorRight:"
//             );

//             // theAdrHigh = (unsigned char *)(HIRES_SCREEN_ADDRESS + multi40[(lin<<1) + lin] + (col>>1));
//             // *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             // *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
//             // wrtAdr += NEXT_SCANLINE_INCREMENT;
//             asm (
//                 "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #120: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #160: sta (_wrtAdr),y:"
//                 "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #200: sta (_wrtAdr),y:"
//                 "lda _wrtAdr: clc: adc #240: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):"
//             );

//             (*dda1StepFunction)();
//             dda2Step2();
//             (*dda3StepFunction)();
//             dda4Step2();


//         }
//         theBaseAdr += 1;
//     }
// }

