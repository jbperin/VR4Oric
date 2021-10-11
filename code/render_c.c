#include "config.h"

#ifdef __USE_PURE_C_RENDER__
void project2Screen () {

    theBaseAdr      = (unsigned char *)(DEFAULT_BASE_ADRESS);

// 1 LOOP OVER COLUMNS
    for (idxCol=VIEWPORT_START_COLUMN; idxCol< SCREEN_WIDTH; idxCol+=2) {
// 1.1 INIT COLUMN
        wrtAdr              = theBaseAdr;

// 1.2 INIT HIGH LINES 

// 1.2.1 INIT DDA COMMON

// 1.2.2 INIT DDA 1 SPECIFIC        

        dda1StartValue       = tabLowX[idxCol];
        dda1EndValue         = tabMiddleX[idxCol];
        dda1NbStep           = SCREEN_HEIGHT/2;
        dda1Init();

        dda2StartValue       = tabLowY[idxCol];
        dda2EndValue         = tabMiddleY[idxCol];
        dda2NbStep           = SCREEN_HEIGHT/2;
        dda2Init();

// 1.2.3 INIT DDA 3 SPECIFIC 
        dda3StartValue       = tabLowX[idxCol+1];
        dda3EndValue         = tabMiddleX[idxCol+1];
        dda3NbStep           = SCREEN_HEIGHT/2;
        dda3Init();

        dda4StartValue       = tabLowY[idxCol+1];
        dda4EndValue         = tabMiddleY[idxCol+1];
        dda4NbStep           = SCREEN_HEIGHT/2;
        dda4Init();

// 1.3 LOOP OVER HIGH LINES 
        for (idxLin=0; idxLin< SCREEN_HEIGHT/2; idxLin+=2) {

// 1.3.1 TOP PIXEL 

// 1.3.1.1 TOP LEFT PIXEL COORDINATE 
            theX   = dda1CurrentValue + rollCoord;
            theY   = dda2CurrentValue;
// 1.3.1.2 TOP LEFT PIXEL COLOR            
            theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.3.1.3 TOP RIGHT PIXEL COORDINATE 
            theX   = dda3CurrentValue + rollCoord;
            theY   = dda4CurrentValue;
// 1.3.1.4 TOP RIGHT PIXEL COLOR
            theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.3.1.5  WRITE TOP PIXEL ON SCREEN
            *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;

// 1.3.2 DDAs STEP
            (*dda1StepFunction)();
            (*dda2StepFunction)();
            (*dda3StepFunction)();
            (*dda4StepFunction)();

// 1.3.3 BOTTOM PIXEL 
// 1.3.3.1 BOTTOM LEFT PIXEL COORDINATE 
            theX   = dda1CurrentValue + rollCoord;
            theY   = dda2CurrentValue;
// 1.3.3.2 BOTTOM LEFT PIXEL COLOR
            theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.3.3.3 BOTTOM RIGHT PIXEL COORDINATE
            theX   = dda3CurrentValue + rollCoord;
            theY   = dda4CurrentValue;
// 1.3.3.4 BOTTOM RIGHT PIXEL COLOR
            theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.3.3.5 WRITE BOTTOM PIXEL ON SCREEN
            *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;

// 1.3.4 DDAs STEP
            (*dda1StepFunction)();
            (*dda2StepFunction)();
            (*dda3StepFunction)();
            (*dda4StepFunction)();


        }

// 1.4 INIT LOW LINES 
// 1.4.1 INIT DDA COMMON

// 1.4.2 INIT DDA 1 SPECIFIC

        dda1StartValue       = tabMiddleX[idxCol];
        dda1EndValue         = tabHighX[idxCol];
        dda1NbStep           = SCREEN_HEIGHT/2;
        dda1Init();

        dda2StartValue       = tabMiddleY[idxCol];
        dda2EndValue         = tabHighY[idxCol];
        dda2NbStep           = SCREEN_HEIGHT/2;
        dda2Init();

// 1.4.3  INIT DDA 3 SPECIFIC

        dda3StartValue       = tabMiddleX[idxCol+1];
        dda3EndValue         = tabHighX[idxCol+1];
        dda3NbStep           = SCREEN_HEIGHT/2;
        dda3Init();

        dda4StartValue       = tabMiddleY[idxCol+1];
        dda4EndValue         = tabHighY[idxCol+1];
        dda4NbStep           = SCREEN_HEIGHT/2;
        dda4Init();

// 1.5 LOOP OVER LOW LINES
        for (idxLin=SCREEN_HEIGHT/2; idxLin< SCREEN_HEIGHT; idxLin+=2) {

// 1.5.1 TOP PIXEL 

// 1.5.1.1 TOP LEFT PIXEL COORDINATE 
            theX   = dda1CurrentValue + rollCoord;
            theY   = dda2CurrentValue;
// 1.5.1.2 TOP LEFT PIXEL COLOR            
            theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.5.1.3 TOP RIGHT PIXEL COORDINATE 
            theX   = dda3CurrentValue + rollCoord;
            theY   = dda4CurrentValue;
// 1.5.1.4 TOP RIGHT PIXEL COLOR
            theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.5.1.5  WRITE TOP PIXEL ON SCREEN
            *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;

// 1.5.2 DDAs STEP
            (*dda1StepFunction)();
            (*dda2StepFunction)();
            (*dda3StepFunction)();
            (*dda4StepFunction)();

// 1.5.3 BOTTOM PIXEL 
// 1.5.3.1 BOTTOM LEFT PIXEL COORDINATE 
            theX   = dda1CurrentValue + rollCoord;
            theY   = dda2CurrentValue;
// 1.5.3.2 BOTTOM LEFT PIXEL COLOR
            theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.5.3.3 BOTTOM RIGHT PIXEL COORDINATE
            theX   = dda3CurrentValue + rollCoord;
            theY   = dda4CurrentValue;
// 1.5.3.4 BOTTOM RIGHT PIXEL COLOR
            theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];

// 1.5.3.5 WRITE BOTTOM PIXEL ON SCREEN            
            *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;
            *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
            wrtAdr += NEXT_SCANLINE_INCREMENT;

// 1.5.4 DDAs STEP
            (*dda1StepFunction)();
            (*dda2StepFunction)();
            (*dda3StepFunction)();
            (*dda4StepFunction)();

        }

// 1.6 NEXT COL
        theBaseAdr += 1;
    }
}
#endif // __USE_PURE_C_RENDER__



#ifdef __USE_C_ASM_RENDER__

// ==============================
// ==============================
// ==============================
// ==============================

void project2ScreenCASM () {
    theBaseAdr      = (unsigned char *)(DEFAULT_BASE_ADRESS);

    asm (
        "lda #32:"
        "sta _dda1NbStep:"
        "sta _dda2NbStep:"
        "sta _dda3NbStep:"
        "sta _dda4NbStep:"
    ); // FIXME: replace 32 by SCREEN_HEIGHT/2


// 1 LOOP OVER COLUMNS
    for (idxCol=VIEWPORT_START_COLUMN; idxCol< SCREEN_WIDTH; idxCol+=2) {

// 1.1 INIT COLUMN

        // wrtAdr              = theBaseAdr;
        asm ("lda _theBaseAdr: sta _wrtAdr: lda _theBaseAdr+1: sta _wrtAdr+1:");

// 1.2 INIT HIGH LINES 
// 1.2.1 INIT DDA COMMON
        // dda1CurrentValue     = (dda1StartValue = tabLowX[idxCol]);
        // dda1EndValue         = tabMiddleX[idxCol];
        // dda2CurrentValue     = (dda2StartValue       = tabLowY[idxCol]);
        // dda2EndValue         = tabMiddleY[idxCol];
        // dda3CurrentValue     = (dda3StartValue       = tabLowX[idxCol+1]);
        // dda3EndValue         = tabMiddleX[idxCol+1];
        // dda4CurrentValue     = (dda4StartValue       = tabLowY[idxCol+1]);
        // dda4EndValue         = tabMiddleY[idxCol+1];
        // dda2NbVal            = dda2EndValue-dda2StartValue;
        // dda4NbVal            = dda4EndValue-dda4StartValue;

        asm (
            "ldy _idxCol:"
            " lda _tabLowX, y: sta _dda1StartValue: sta _dda1CurrentValue: lda _tabMiddleX, y: sta _dda1EndValue:"
            " lda _tabLowY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabMiddleY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:"
            "iny:"
            " lda _tabLowX, y: sta _dda3StartValue: sta _dda3CurrentValue: lda _tabMiddleX, y: sta _dda3EndValue:"
            " lda _tabLowY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabMiddleY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:"
            );


        // dda4CurrentError     = (dda4NbStep           = SCREEN_HEIGHT/2);
        // dda3NbStep           = SCREEN_HEIGHT/2;
        // dda2CurrentError     = (dda2NbStep           = SCREEN_HEIGHT/2);
        // dda1NbStep           = SCREEN_HEIGHT/2;

        asm (
            "lda #32:"
            "sta _dda2CurrentError:"
            "sta _dda4CurrentError:"
        ); // FIXME: replace 32 by SCREEN_HEIGHT/2


        // if (dda1EndValue > dda1StartValue) {
        //     dda1NbVal        = dda1EndValue-dda1StartValue;
        //     dda1Increment    = 1;
        // } else {
        //     dda1NbVal        = dda1StartValue-dda1EndValue;
        //     dda1Increment    = -1;
        // }
// 1.2.2 INIT DDA 1 SPECIFIC        
        asm (
            ":.(:"
            "lda _dda1StartValue:cmp _dda1EndValue:bcs else:"
                "lda _dda1EndValue: "
                "sec: sbc _dda1StartValue: sta _dda1NbVal:"
                "lda #1: sta _dda1Increment:"
            "jmp endif:else:"
                "sbc _dda1EndValue: sta _dda1NbVal:"
                "lda #$FF: sta _dda1Increment:"
            ":endif:.):"
        );


        // if          (dda1NbVal > dda1NbStep) {
        //     dda1CurrentError     = dda1NbVal;
        //     dda1StepFunction     = &dda1Step1;
        // } else if   (dda1NbVal < dda1NbStep) {
        //     dda1CurrentError     = dda1NbStep;
        //     dda1StepFunction     = &dda1Step2;
        // } else {
        //     dda1CurrentError     = dda1EndValue;
        //     dda1StepFunction     = &dda1Step0;
        // }


asm (
            // ".("
            "lda _dda1NbStep:"
            "cmp _dda1NbVal:"
            "beq NbStepEqualsNbVal_1234:"
            "bcs NbStepGreaterThanNbVal_1234:"
                "lda _dda1NbVal:"
                "sta _dda1CurrentError:"
                "lda #<(_dda1Step1ASM):"
                "sta _dda1StepFunction:"
                "lda #>(_dda1Step1ASM):"
                "sta _dda1StepFunction+1:"
            "jmp dda1InitDone_1234:"
                );
                asm(
            "NbStepGreaterThanNbVal_1234    :"
                "lda _dda1NbStep:"
                "sta _dda1CurrentError:"
                "lda #<(_dda1Step2ASM):"
                "sta _dda1StepFunction:"
                "lda #>(_dda1Step2ASM):"
                "sta _dda1StepFunction+1:"
            "jmp dda1InitDone_1234:"
                );
                asm(
            "NbStepEqualsNbVal_1234    :"
                "lda _dda1EndValue:"
                "sta _dda1CurrentError:"
                "lda #<(_dda1Step0ASM):"
                "sta _dda1StepFunction:"
                "lda #>(_dda1Step0ASM):"
                "sta _dda1StepFunction+1:"
            "dda1InitDone_1234:"
            // ".):"
);


// 1.2.3 INIT DDA 3 SPECIFIC 
        // if (dda3EndValue > dda3StartValue) {
        //     dda3NbVal                = dda3EndValue-dda3StartValue;
        //     dda3Increment            = 1;
        // } else {
        //     dda3NbVal                = dda3StartValue-dda3EndValue;
        //     dda3Increment            = -1;
        // }

        {asm (
            ":.(:"
            "lda _dda3StartValue: cmp _dda3EndValue: bcs else:"
                "lda _dda3EndValue: sec: sbc _dda3StartValue: sta _dda3NbVal:"
                "lda #1: sta _dda3Increment:"
            "jmp endif:else:"
                "sbc _dda3EndValue: sta _dda3NbVal:"
                "lda #$FF: sta _dda3Increment:"
            ":endif:.):"
        );}
        // if (dda3NbVal > dda3NbStep) {
        //     dda3CurrentError     = dda3NbVal;
        //     dda3StepFunction     = &dda3Step1;
        // } else if   (dda3NbVal < dda3NbStep) {
        //     dda3CurrentError     = dda3NbStep;
        //     dda3StepFunction     = &dda3Step2;
        // } else {
        //     dda3CurrentError     = dda3EndValue;
        //     dda3StepFunction     = &dda3Step0;
        // }

asm (
    // ".("
    "lda _dda3NbStep:"
    "cmp _dda3NbVal:"
    "beq NbStepEqualsNbVal_4321:"
    "bcs NbStepGreaterThanNbVal_4321:"
        "lda _dda3NbVal:sta _dda3CurrentError:"
        "lda #<(_dda3Step1ASM):sta _dda3StepFunction:lda #>(_dda3Step1ASM):sta _dda3StepFunction+1:"
    "jmp dda3InitDone_4321:"
        );
        asm(
    "NbStepGreaterThanNbVal_4321    :"
        "lda _dda3NbStep:sta _dda3CurrentError:"
        "lda #<(_dda3Step2ASM):sta _dda3StepFunction:lda #>(_dda3Step2ASM):sta _dda3StepFunction+1:"
    "jmp dda3InitDone_4321:"
        );
        asm(
    "NbStepEqualsNbVal_4321    :"
        "lda _dda3EndValue:sta _dda3CurrentError:"
        "lda #<(_dda3Step0ASM):sta _dda3StepFunction:lda #>(_dda3Step0ASM):sta _dda3StepFunction+1:"
    "dda3InitDone_4321:"
    // ".):"
);

// 1.3 LOOP OVER HIGH LINES 
        for (idxLin=0; idxLin< SCREEN_HEIGHT/2; idxLin+=2) {

// 1.3.1 TOP PIXEL
// 1.3.1.1 TOP LEFT PIXEL COORDINATE  
            // theX    = dda1CurrentValue + rollCoord;
            // theY    = dda2CurrentValue;
            // {asm (
            //     "lda _dda1CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda2CurrentValue: sta _theY:"
            // );}

// 1.3.1.2 TOP LEFT PIXEL COLOR   
            // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // { asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorLeft:"
            // );}
            {asm (
                "lda _dda1CurrentValue: clc: adc _rollCoord: tay:"
                "lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda2CurrentValue: lda (_myTmp),y:"
                "sta _theColorLeft:"
            );}

// 1.3.1.3 TOP RIGHT PIXEL COORDINATE
            // theX   = dda3CurrentValue + rollCoord;
            // theY   = dda4CurrentValue;
            // {asm (
            //     "lda _dda3CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda4CurrentValue: sta _theY:"
            // );}

// 1.3.1.4 TOP RIGHT PIXEL COLOR
            // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // {asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorRight:"
            // );}
            {asm (
                "lda _dda3CurrentValue: clc: adc _rollCoord: tay:"
                "ldy _theX:lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda4CurrentValue: lda (_myTmp),y:"
                "sta _theColorRight:"
            );}

// 1.3.1.5  WRITE TOP PIXEL ON SCREEN
            // *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            {asm (
                // "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #0: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #40: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #80: sta (_wrtAdr),y:"
                "ldy _theColorLeft:ldx _theColorRight:"
                "lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #0: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #40: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #80: sta (_wrtAdr),y:"
            );}


// 1.3.2 DDAs STEP

            (*dda1StepFunction)();

            // dda2CurrentError         -= dda2NbVal; // dda2EndValue-dda2StartValue;
            // if ((dda2CurrentError<<1) < dda2NbStep) {
            //     dda2CurrentError     += dda2NbStep;
            //     dda2CurrentValue     ++;
            // }
            {asm(
                "lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):"
            );}

            (*dda3StepFunction)();

            // dda4CurrentError         -= dda4NbVal; 
            // if ((dda4CurrentError<<1) < dda4NbStep) {
            //     dda4CurrentError     += dda4NbStep;
            //     dda4CurrentValue     ++;
            // }
            {asm(
                "lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):"
            );}

// 1.3.3 BOTTOM PIXEL 
// 1.3.3.1 BOTTOM LEFT PIXEL COORDINATE 
            // theX    = dda1CurrentValue + rollCoord;
            // theY    = dda2CurrentValue;
            // {asm (
            //     "lda _dda1CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda2CurrentValue: sta _theY:"
            // );}

// 1.3.3.2 BOTTOM LEFT PIXEL COLOR
            // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // {asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorLeft:"
            // );}
            {asm (
                "lda _dda1CurrentValue: clc: adc _rollCoord: tay:"
                "lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda2CurrentValue: lda (_myTmp),y:"
                "sta _theColorLeft:"
            );}


// 1.3.3.3 BOTTOM RIGHT PIXEL COORDINATE

            // theX   = dda3CurrentValue + rollCoord;
            // theY   = dda4CurrentValue;
            {asm (
                "lda _dda3CurrentValue: clc: adc _rollCoord: sta _theX:"
                "lda _dda4CurrentValue: sta _theY:"
            );}

// 1.3.3.4 BOTTOM RIGHT PIXEL COLOR

            // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
            {asm (
                "ldy _theX:"
                "lda _adrTextureLow,y:"
                "sta _myTmp:"
                "lda _adrTextureHigh,y:"
                "sta _myTmp+1:"
                "ldy _theY:"
                "lda (_myTmp),y:"
                "sta _theColorRight:"
            );}
            // {asm (
            //     "lda _dda3CurrentValue: clc: adc _rollCoord: tay:"
            //     "lda _adrTextureLow,y: sta _myTmp: lda _adrTextureHigh,y: sta _myTmp+1:"
            //     "ldy _dda4CurrentValue: lda (_myTmp),y:"
            //     "sta _theColorRight:"
            // );}
            
// 1.3.3.5 WRITE BOTTOM PIXEL ON SCREEN
            // *wrtAdr = tabLeftRed[theColorLeft]  | tabRightRed[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftBlue[theColorLeft]  | tabRightBlue[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            {asm (
                // "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #120: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #160: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #200: sta (_wrtAdr),y:"
                "ldy _theColorLeft:ldx _theColorRight:"
                "lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #120: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #160: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #200: sta (_wrtAdr),y:"
                "lda _wrtAdr: clc: adc #240: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):"
            );}

// 1.3.4 DDAs STEP

            (*dda1StepFunction)();

            // dda2CurrentError         -= dda2NbVal; // dda2EndValue-dda2StartValue;
            // if ((dda2CurrentError<<1) < dda2NbStep) {
            //     dda2CurrentError     += dda2NbStep;
            //     dda2CurrentValue     ++;
            // }
            {asm(
                "lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):"
            );}

            (*dda3StepFunction)();

            // dda4CurrentError         -= dda4NbVal; 
            // if ((dda4CurrentError<<1) < dda4NbStep) {
            //     dda4CurrentError     += dda4NbStep;
            //     dda4CurrentValue     ++;
            // }
            {asm(
                "lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):"
            );}


        }

// 1.4 INIT LOW LINES 
// 1.4.1 INIT DDA COMMON
        // dda1CurrentValue         = (dda1StartValue       = tabMiddleX[idxCol]);
        // dda1EndValue         = tabHighX[idxCol];
        // dda2CurrentValue         = (dda2StartValue       = tabMiddleY[idxCol]);
        // dda2EndValue         = tabHighY[idxCol];
        // dda3CurrentValue         = (dda3StartValue       = tabMiddleX[idxCol+1]);
        // dda3EndValue         = tabHighX[idxCol+1];
        // dda4CurrentValue         = (dda4StartValue       = tabMiddleY[idxCol+1]);
        // dda4EndValue         = tabHighY[idxCol+1];
        // dda2NbVal                = dda2EndValue-dda2StartValue;
        // dda4NbVal                = dda4EndValue-dda4StartValue;

        {asm (
            "ldy _idxCol:"
            " lda _tabMiddleX, y: sta _dda1StartValue: sta _dda1CurrentValue: lda _tabHighX, y: sta _dda1EndValue:"
            " lda _tabMiddleY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabHighY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:"
            "iny:"
            " lda _tabMiddleX, y: sta _dda3StartValue: sta _dda3CurrentValue: lda _tabHighX, y: sta _dda3EndValue:"
            " lda _tabMiddleY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabHighY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:"
            );}

        // dda1NbStep           = SCREEN_HEIGHT/2;
        // dda2CurrentError     = (dda2NbStep           = SCREEN_HEIGHT/2);
        // dda3NbStep           = SCREEN_HEIGHT/2;
        // dda4CurrentError     = (dda4NbStep           = SCREEN_HEIGHT/2);
        {asm (
            "lda #32:"
            "sta _dda2CurrentError:"
            "sta _dda4CurrentError:"
        );} // FIXME: replace 32 by SCREEN_HEIGHT/2

// 1.4.2 INIT DDA 1 SPECIFIC
        // if (dda1EndValue > dda1StartValue) {
        //     dda1NbVal                = dda1EndValue-dda1StartValue;
        //     dda1Increment            = 1;
        // } else {
        //     dda1NbVal                = dda1StartValue-dda1EndValue;
        //     dda1Increment            = -1;
        // }
        {asm (
            ":.(:"
            "lda _dda1StartValue: cmp _dda1EndValue: bcs else:"
                "lda _dda1EndValue: sec: sbc _dda1StartValue: sta _dda1NbVal:"
                "lda #1: sta _dda1Increment:"
            "jmp endif:else:"
                "sbc _dda1EndValue: sta _dda1NbVal:"
                "lda #$FF: sta _dda1Increment:"
            ":endif:.):"
        );}

        // if          (dda1NbVal > dda1NbStep) {
        //     dda1CurrentError     = dda1NbVal;
        //     dda1StepFunction     = &dda1Step1;
        // } else if   (dda1NbVal < dda1NbStep) {
        //     dda1CurrentError     = dda1NbStep;
        //     dda1StepFunction     = &dda1Step2;
        // } else {
        //     dda1CurrentError     = dda1EndValue;
        //     dda1StepFunction     = &dda1Step0;
        // }


        {asm (
            // ".("
            "lda _dda1NbStep:"
            "cmp _dda1NbVal:"
            "beq NbStepEqualsNbVal_5678:"
            "bcs NbStepGreaterThanNbVal_5678:"
                "lda _dda1NbVal: sta _dda1CurrentError:"
                "lda #<(_dda1Step1ASM): sta _dda1StepFunction: lda #>(_dda1Step1ASM):sta _dda1StepFunction+1:"
            "jmp dda1InitDone_5678:"
                );
                asm(
            "NbStepGreaterThanNbVal_5678    :"
                "lda _dda1NbStep: sta _dda1CurrentError:"
                "lda #<(_dda1Step2ASM): sta _dda1StepFunction: lda #>(_dda1Step2ASM): sta _dda1StepFunction+1:"
            "jmp dda1InitDone_5678:"
                );
                asm(
            "NbStepEqualsNbVal_5678    :"
                "lda _dda1EndValue: sta _dda1CurrentError:"
                "lda #<(_dda1Step0ASM):sta _dda1StepFunction:lda #>(_dda1Step0ASM):sta _dda1StepFunction+1:"
            "dda1InitDone_5678:"
            // ".):"
        );}

// 1.4.3  INIT DDA 3 SPECIFIC
        // if (dda3EndValue > dda3StartValue) {
        //     dda3NbVal                = dda3EndValue-dda3StartValue;
        //     dda3Increment            = 1;
        // } else {
        //     dda3NbVal                = dda3StartValue-dda3EndValue;
        //     dda3Increment            = -1;
        // }
        {asm (
            ":.(:"
            "lda _dda3StartValue: cmp _dda3EndValue:bcs else:"
                "lda _dda3EndValue: sec: sbc _dda3StartValue: sta _dda3NbVal:"
                "lda #1: sta _dda3Increment:"
            "jmp endif: else:"
                "sbc _dda3EndValue: sta _dda3NbVal:"
                "lda #$FF: sta _dda3Increment:"
            "endif:.):"
        );}


        // if          (dda3NbVal > dda3NbStep) {
        //     dda3CurrentError     = dda3NbVal;
        //     dda3StepFunction     = &dda3Step1;
        // } else if   (dda3NbVal < dda3NbStep) {
        //     dda3CurrentError     = dda3NbStep;
        //     dda3StepFunction     = &dda3Step2;
        // } else {
        //     dda3CurrentError     = dda3EndValue;
        //     dda3StepFunction     = &dda3Step0;
        // }
{asm (
    // ".("
    "lda _dda3NbStep:"
    "cmp _dda3NbVal:"
    "beq NbStepEqualsNbVal_8765:"
    "bcs NbStepGreaterThanNbVal_8765:"
        "lda _dda3NbVal: sta _dda3CurrentError:"
        "lda #<(_dda3Step1ASM): sta _dda3StepFunction: lda #>(_dda3Step1ASM): sta _dda3StepFunction+1:"
    "jmp dda3InitDone_8765:"
        );
        asm(
    "NbStepGreaterThanNbVal_8765    :"
        "lda _dda3NbStep: sta _dda3CurrentError:"
        "lda #<(_dda3Step2ASM): sta _dda3StepFunction: lda #>(_dda3Step2ASM): sta _dda3StepFunction+1:"
    "jmp dda3InitDone_8765:"
        );
        asm(
    "NbStepEqualsNbVal_8765    :"
        "lda _dda3EndValue: sta _dda3CurrentError:"
        "lda #<(_dda3Step0ASM): sta _dda3StepFunction: lda #>(_dda3Step0ASM): sta _dda3StepFunction+1:"
    "dda3InitDone_8765:"
    // ".):"
);}

// 1.5 LOOP OVER LOW LINES

        for (idxLin=SCREEN_HEIGHT/2; idxLin< SCREEN_HEIGHT; idxLin+=2) {

// 1.5.1 TOP PIXEL 
// 1.5.1.1 TOP LEFT PIXEL COORDINATE  
            // theX   = dda1CurrentValue + rollCoord;
            // theY   = dda2CurrentValue;
            // {asm (
            //     "lda _dda1CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda2CurrentValue: sta _theY:"
            // );}
// 1.5.1.2 TOP LEFT PIXEL COLOR               
            // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // {asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorLeft:"
            // );}
            {asm (
                "lda _dda1CurrentValue: clc: adc _rollCoord: tay:"
                "lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda2CurrentValue: lda (_myTmp),y:"
                "sta _theColorLeft:"
            );}

// 1.5.1.3 TOP RIGHT PIXEL COORDINATE 
            // theX   = dda3CurrentValue + rollCoord;
            // theY   = dda4CurrentValue;
            // {asm (
            //     "lda _dda3CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda4CurrentValue: sta _theY:"
            // );}
// 1.5.1.4 TOP RIGHT PIXEL COLOR            
            // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // {asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorRight:"
            // );}
            {asm (
                "lda _dda3CurrentValue: clc: adc _rollCoord: tay:"
                "lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda4CurrentValue: lda (_myTmp),y:"
                "sta _theColorRight:"
            );}
 
// 1.5.1.5  WRITE TOP PIXEL ON SCREEN
            // *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            {asm (
                // "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #0: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #40: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #80: sta (_wrtAdr),y:"
                "ldy _theColorLeft:ldx _theColorRight:"
                "lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #0: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #40: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #80: sta (_wrtAdr),y:"
            );}


// 1.5.2 DDAs STEP
            (*dda1StepFunction)();

            // dda2CurrentError         -= dda2NbVal;
            // if ((dda2CurrentError<<1) < dda2NbStep) {
            //     dda2CurrentError     += dda2NbStep;
            //     dda2CurrentValue     ++;
            // }
            {asm(
                "lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):"
            );}


            (*dda3StepFunction)();

            // dda4CurrentError         -= dda4NbVal; 
            // if ((dda4CurrentError<<1) < dda4NbStep) {
            //     dda4CurrentError     += dda4NbStep;
            //     dda4CurrentValue     ++;
            // }
            {asm(
                "lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):"
            );}


// 1.5.3 BOTTOM PIXEL 
// 1.5.3.1 BOTTOM LEFT PIXEL COORDINATE 
            // theX   = dda1CurrentValue + rollCoord;
            // theY   = dda2CurrentValue;
            // {asm (
            //     "lda _dda1CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda2CurrentValue: sta _theY:"
            // );}
// 1.5.3.2 BOTTOM LEFT PIXEL COLOR
            // theColorLeft = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // {asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorLeft:"
            // );}
            {asm (
                "lda _dda1CurrentValue: clc: adc _rollCoord: tay:"
                "lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda2CurrentValue: lda (_myTmp),y:"
                "sta _theColorLeft:"
            );}

// 1.5.3.3 BOTTOM RIGHT PIXEL COORDINATE
            // theX   = dda3CurrentValue + rollCoord;
            // theY   = dda4CurrentValue;
            // {asm (
            //     "lda _dda3CurrentValue: clc: adc _rollCoord: sta _theX:"
            //     "lda _dda4CurrentValue: sta _theY:"
            // );}
// 1.5.3.4 BOTTOM RIGHT PIXEL COLOR
            // theColorRight = texture_PANO[theX*IMAGE_HEIGHT+theY];
            // {asm (
            //     "ldy _theX:"
            //     "lda _adrTextureLow,y:"
            //     "sta _myTmp:"
            //     "lda _adrTextureHigh,y:"
            //     "sta _myTmp+1:"
            //     "ldy _theY:"
            //     "lda (_myTmp),y:"
            //     "sta _theColorRight:"
            // );}
            {asm (
                "lda _dda3CurrentValue: clc: adc _rollCoord: tay:"
                "lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:"
                "ldy _dda4CurrentValue: lda (_myTmp),y:"
                "sta _theColorRight:"
            );}
 
// 1.5.3.5 WRITE BOTTOM PIXEL ON SCREEN  
            // *wrtAdr = tabLeftRed[theColorLeft]    | tabRightRed[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftGreen[theColorLeft]  | tabRightGreen[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            // *wrtAdr = tabLeftBlue[theColorLeft]   | tabRightBlue[theColorRight];
            // wrtAdr += NEXT_SCANLINE_INCREMENT;
            {asm (
                // "ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #120: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #160: sta (_wrtAdr),y:"
                // "ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #200: sta (_wrtAdr),y:"
                "ldy _theColorLeft:ldx _theColorRight:"
                "lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #120: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #160: sta (_wrtAdr),y:"
                "ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #200: sta (_wrtAdr),y:"
                "lda _wrtAdr: clc: adc #240: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):"
            );}

// 1.5.4 DDAs STEP
            (*dda1StepFunction)();

            // dda2CurrentError         -= dda2NbVal;
            // if ((dda2CurrentError<<1) < dda2NbStep) {
            //     dda2CurrentError     += dda2NbStep;
            //     dda2CurrentValue     ++;
            // }
            {asm(
                "lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):"
            );}

            (*dda3StepFunction)();


            // dda4CurrentError         -= dda4NbVal; 
            // if ((dda4CurrentError<<1) < dda4NbStep) {
            //     dda4CurrentError     += dda4NbStep;
            //     dda4CurrentValue     ++;
            // }
            {asm(
                "lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:"
                ":.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):"
            );}
       }
// 1.6 NEXT COL
        // theBaseAdr += 1;
        {asm("lda _theBaseAdr: clc: adc #1: sta _theBaseAdr :.(: bcc skip:    inc _theBaseAdr+1: skip: .):");}
    }
}
#endif // __USE_C_ASM_RENDER__
