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



char IsHires=0;
unsigned char running ;
unsigned char waiting ;
unsigned char refreshNeeded = 1;

unsigned char scene_number = 0;
unsigned char has_key   =   0;

#include "render_c.c"

unsigned char diff_index;
int nbval, diffidx;

void apply_diff(){
    
    nbval = diffimg[1]*256 + diffimg[2]; // 508 ; //(int)(((int)diffimg[1])<<8 + diffimg[2]);
    for (diffidx=0; diffidx< nbval; diffidx++){
        theX = diffimg[(diffidx*3)+3];
        theY = diffimg[(diffidx*3)+3+1];
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
}


void keyPressed(unsigned char c){

    waiting = 0;

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

void PROJECT (){
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
}

char message[]="coucou\0";
void main()
{
    int ii = 0;
    SwitchToText();

    for (ii=0; ii < 256; ii++) {
        adrTextureHigh[ii] = (unsigned char)((((int)texture_PANO) + 128*ii)>>8);
        adrTextureLow[ii] = (unsigned char)(((((int)texture_PANO) + 128*ii) & 0x00FF));
    }
    LoadFileAt(LOADER_BTABLES, borderTables);

    kernelInit();

    LoadFileAt(LOADER_PANO_01, texture_PANO);
    LoadFileAt(LOADER_DIFFIMG, diffimg);
    LoadFileAt(LOADER_FONT_6x8, 0xb500);

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
                PROJECT();
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



