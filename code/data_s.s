#include "config.h"

.bss
* = $400
_texture_PANO .dsb 32768 ;; 256*128

_adrTextureHigh .dsb 256
_adrTextureLow .dsb 256

_borderTables .dsb 1014 ;; 13*78

.text

;; #include "image_s.s"
;; #include "tabEquiRect_s.s"



.zero

_wrtAdr .dsb 2
_myTmp .dsb 2
_theBaseAdr .dsb 2
_theColorLeft        .dsb 1
_theColorRight      .dsb 1
_idxCol .dsb 1
_idxLin .dsb 1


_theX .dsb 1
_theY .dsb 1


_dda1NbStep         .dsb 1
_dda1StartValue     .dsb 1

_dda1CurrentValue   .dsb 1
_dda1EndValue       .dsb 1
_dda1NbVal          .dsb 1
_dda1CurrentError   .dsb 1
;; _dda1StepFunction   .dsb 2 
_dda1Increment      .dsb 1

_dda2NbStep         .dsb 1
_dda2StartValue     .dsb 1

_dda2CurrentValue   .dsb 1
_dda2EndValue       .dsb 1
_dda2NbVal          .dsb 1
_dda2CurrentError   .dsb 1
;; _dda2StepFunction   .dsb 2 
;; _dda2Increment      .dsb 1

_dda3NbStep         .dsb 1
_dda3StartValue     .dsb 1

_dda3CurrentValue   .dsb 1
_dda3EndValue       .dsb 1
_dda3NbVal          .dsb 1
_dda3CurrentError   .dsb 1
;; _dda3StepFunction   .dsb 2 
_dda3Increment      .dsb 1

_dda4NbStep         .dsb 1
_dda4StartValue     .dsb 1

_dda4CurrentValue   .dsb 1
_dda4EndValue       .dsb 1
_dda4NbVal          .dsb 1
_dda4CurrentError   .dsb 1
;; _dda4StepFunction   .dsb 2 
;; _dda4Increment      .dsb 1


#ifndef __USE_C_DDA__
.text


; void ddaStep0(){
;     ddaCurrentValue         += dda1Increment;
; }
_dda1Step0ASM
.(
    lda         _dda1CurrentValue
    clc
    adc         _dda1Increment
    sta         _dda1CurrentValue
.)
    rts

; void ddaStep1(){
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
;         ddaCurrentError         -= ddaNbStep;
;         ddaCurrentValue         += dda1Increment;
;     }
;     ddaCurrentError     += ddaNbVal;
; }
_dda1Step1ASM
.(
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
loop
    lda         _dda1CurrentError
    bmi         end_loop
    asl         
    cmp         _dda1NbStep
    bcc         end_loop
            lda         _dda1CurrentError
            sec ;; FIXME : this sec is useless
            sbc         _dda1NbStep
            sta         _dda1CurrentError
            lda         _dda1CurrentValue
            clc
            adc         _dda1Increment
            sta         _dda1CurrentValue
    jmp         loop
end_loop
    lda         _dda1CurrentError
    clc
    adc         _dda1NbVal
    sta         _dda1CurrentError
.)
    rts


; void ddaStep2(){
;     ddaCurrentError         -= ddaNbVal;
;     if ((ddaCurrentError<<1) < ddaNbStep) {
;         ddaCurrentError     += ddaNbStep;
;         ddaCurrentValue     += ddaIncrement;
;     }
; }
_dda1Step2ASM
.(
    lda         _dda1CurrentError
    sec
    sbc         _dda1NbVal
    sta         _dda1CurrentError
;     if ((ddaCurrentError<<1) < ddaNbStep) {
    bmi         updateError
    asl
    cmp         _dda1NbStep
    bcc         updateError
    rts
updateError
;         ddaCurrentError     += ddaNbStep;
            lda         _dda1CurrentError
            clc
            adc         _dda1NbStep
            sta         _dda1CurrentError
;         ddaCurrentValue     += _dda1Increment;
            lda         _dda1CurrentValue
            clc
            adc         _dda1Increment
            sta         _dda1CurrentValue
;     }

.)
    rts



; void ddaStep0(){
;     ddaCurrentValue         += ddaIncrement;
; }
_dda3Step0ASM
.(
    lda         _dda3CurrentValue
    clc
    adc         _dda3Increment
    sta         _dda3CurrentValue
.)
    rts

; void ddaStep1(){
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
;         ddaCurrentError         -= ddaNbStep;
;         ddaCurrentValue         += 1;
;     }
;     ddaCurrentError     += ddaNbVal;
; }
_dda3Step1ASM
.(
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
loop
    lda         _dda3CurrentError
    bmi         end_loop
    asl         
    cmp         _dda3NbStep
    bcc         end_loop
            lda         _dda3CurrentError
            sec ;; FIXME : this sec is useless
            sbc         _dda3NbStep
            sta         _dda3CurrentError
            lda         _dda3CurrentValue
            clc
            adc         _dda3Increment
            sta         _dda3CurrentValue
    jmp         loop
end_loop
    lda         _dda3CurrentError
    clc
    adc         _dda3NbVal
    sta         _dda3CurrentError
.)
    rts


; void ddaStep2(){
;     ddaCurrentError         -= ddaNbVal;
;     if ((ddaCurrentError<<1) < ddaNbStep) {
;         ddaCurrentError     += ddaNbStep;
;         ddaCurrentValue     += 1;
;     }
; }
_dda3Step2ASM
.(
    lda         _dda3CurrentError
    sec
    sbc         _dda3NbVal
    sta         _dda3CurrentError
;     if ((ddaCurrentError<<1) < ddaNbStep) {
    bmi         updateError
    asl
    cmp         _dda3NbStep
    bcc         updateError
    rts
updateError
;         ddaCurrentError     += ddaNbStep;
            lda         _dda3CurrentError
            clc
            adc         _dda3NbStep
            sta         _dda3CurrentError
;         ddaCurrentValue     += dda3Increment;
            lda _dda3CurrentValue:clc: adc _dda3Increment: sta _dda3CurrentValue
;     }

.)
    rts


breakhere:
_project2ScreenPureASM:.(


    ;; theBaseAdr      = (unsigned char *)(DEFAULT_BASE_ADRESS);
    lda #<(DEFAULT_BASE_ADRESS)
    sta _theBaseAdr
    lda #>(DEFAULT_BASE_ADRESS)
    sta _theBaseAdr+1

    lda #32:
    sta _dda1NbStep:
    sta _dda2NbStep:
    sta _dda3NbStep:
    sta _dda4NbStep:


;; 1 LOOP OVER COLUMNS
    lda  #VIEWPORT_START_COLUMN
    sta  _idxCol
    ;; for (idxCol=VIEWPORT_START_COLUMN; idxCol< SCREEN_WIDTH; idxCol+=2) {
loopOnIdxCol_01

;; 1.1 INIT COLUMN
        ;; wrtAdr = theBaseAdr;
        lda _theBaseAdr: sta _wrtAdr: lda _theBaseAdr+1: sta _wrtAdr+1:

;; 1.2 INIT HIGH LINES
;; 1.2.1 INIT DDA COMMON
        ldy _idxCol:
        lda _tabLowX, y: sta _dda1StartValue: sta _dda1CurrentValue: lda _tabMiddleX, y: sta _dda1EndValue:
        lda _tabLowY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabMiddleY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:
        iny:
        lda _tabLowX, y: sta _dda3StartValue: sta _dda3CurrentValue: lda _tabMiddleX, y: sta _dda3EndValue:
        lda _tabLowY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabMiddleY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:

        lda #(SCREEN_HEIGHT/2)
        sta _dda2CurrentError
        sta _dda4CurrentError

;; 1.2.2 INIT DDA 1 SPECIFIC   
        :.(:
        lda _dda1StartValue:cmp _dda1EndValue:bcs else:
            lda _dda1EndValue: 
            sec: sbc _dda1StartValue: sta _dda1NbVal:
            lda #1: sta _dda1Increment:
        jmp endif:else:
            sbc _dda1EndValue: sta _dda1NbVal:
            lda #$FF: sta _dda1Increment:
        :endif:.):


        lda _dda1NbStep:
        cmp _dda1NbVal:
        beq NbStepEqualsNbVal_1234_00:
        bcs NbStepGreaterThanNbVal_1234_00:
            lda _dda1NbVal:
            sta _dda1CurrentError:
            lda #<(_dda1Step1ASM):
            sta _dda1StepFunction:
            lda #>(_dda1Step1ASM):
            sta _dda1StepFunction+1:
        jmp dda1InitDone_1234_00:
        NbStepGreaterThanNbVal_1234_00    :
            lda _dda1NbStep:
            sta _dda1CurrentError:
            lda #<(_dda1Step2ASM):
            sta _dda1StepFunction:
            lda #>(_dda1Step2ASM):
            sta _dda1StepFunction+1:
        jmp dda1InitDone_1234_00:
        NbStepEqualsNbVal_1234_00    :
            lda _dda1EndValue:
            sta _dda1CurrentError:
            lda #<(_dda1Step0ASM):
            sta _dda1StepFunction:
            lda #>(_dda1Step0ASM):
            sta _dda1StepFunction+1:
dda1InitDone_1234_00 :

;; 1.2.3 INIT DDA 3 SPECIFIC 
        :.(:
        lda _dda3StartValue: cmp _dda3EndValue: bcs else:
            lda _dda3EndValue: sec: sbc _dda3StartValue: sta _dda3NbVal:
            lda #1: sta _dda3Increment:
        jmp endif:else:
            sbc _dda3EndValue: sta _dda3NbVal:
            lda #$FF: sta _dda3Increment:
        :endif:.):

        lda _dda3NbStep:
        cmp _dda3NbVal:
        beq NbStepEqualsNbVal_4321_00:
        bcs NbStepGreaterThanNbVal_4321_00:
            lda _dda3NbVal:
            sta _dda3CurrentError:
            lda #<(_dda3Step1ASM):
            sta _dda3StepFunction:
            lda #>(_dda3Step1ASM):
            sta _dda3StepFunction+1:
        jmp dda3InitDone_4321_00:
            
        NbStepGreaterThanNbVal_4321_00    :
            lda _dda3NbStep:
            sta _dda3CurrentError:
            lda #<(_dda3Step2ASM):
            sta _dda3StepFunction:
            lda #>(_dda3Step2ASM):
            sta _dda3StepFunction+1:
        jmp dda3InitDone_4321_00:
            

        NbStepEqualsNbVal_4321_00    :
            lda _dda3EndValue:
            sta _dda3CurrentError:
            lda #<(_dda3Step0ASM):
            sta _dda3StepFunction:
            lda #>(_dda3Step0ASM):
            sta _dda3StepFunction+1:
dda3InitDone_4321_00:


        ;; ==================

;; 1.3 LOOP OVER HIGH LINES 
        lda #((SCREEN_HEIGHT/4)-1)
        sta _idxLin
        ;; for (idxLin=0; idxLin< SCREEN_HEIGHT/2; idxLin+=2)
loopOnIdxLin_01

;; 1.3.1 TOP PIXEL 
;; 1.3.1.1 TOP LEFT PIXEL COORDINATE 
;; 1.3.1.2 TOP LEFT PIXEL COLOR
            lda _dda1CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda2CurrentValue: lda (_myTmp),y:
            sta _theColorLeft:
;; 1.3.1.3 TOP RIGHT PIXEL COORDINATE
;; 1.3.1.4 TOP RIGHT PIXEL COLOR
            lda _dda3CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda4CurrentValue: lda (_myTmp),y:
            sta _theColorRight:
;; 1.3.1.5  WRITE TOP PIXEL ON SCREEN
            ldy _theColorLeft:ldx _theColorRight:
            lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #0: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #40: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #80: sta (_wrtAdr),y:
;; 1.3.2 DDAs STEP
            lda _dda1StepFunction : sta _myTmp : lda _dda1StepFunction+1 : sta _myTmp+1 :
            .( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :
            lda _dda3StepFunction : sta _myTmp : lda _dda3StepFunction+1 : sta _myTmp+1 :
        	.( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:
            :.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):
            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            :.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):

;; 1.3.3 BOTTOM PIXEL 
;; 1.3.3.1 BOTTOM LEFT PIXEL COORDINATE 
;; 1.3.3.2 BOTTOM LEFT PIXEL COLOR
            lda _dda1CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda2CurrentValue: lda (_myTmp),y:
            sta _theColorLeft:

;; 1.3.3.3 BOTTOM RIGHT PIXEL COORDINATE
;; 1.3.3.4 BOTTOM RIGHT PIXEL COLOR
            ;; lda _dda3CurrentValue: clc: adc _rollCoord: sta _theX:
            ;; lda _dda4CurrentValue: sta _theY:
            ;; ldy _theX:
            ;; lda _adrTextureLow,y:
            ;; sta _myTmp:
            ;; lda _adrTextureHigh,y:
            ;; sta _myTmp+1:
            ;; ldy _theY:
            ;; lda (_myTmp),y:
            ;; sta _theColorRight:

            lda _dda3CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda4CurrentValue: lda (_myTmp),y:
            sta _theColorRight:
;; 1.3.3.5 WRITE BOTTOM PIXEL ON SCREEN
            ;; ldy _theColorLeft: lda _tabLeftRed,y: ldy _theColorRight: ora _tabRightRed,y: ldy #120: sta (_wrtAdr),y:
            ;; ldy _theColorLeft: lda _tabLeftGreen,y: ldy _theColorRight: ora _tabRightGreen,y: ldy #160: sta (_wrtAdr),y:
            ;; ldy _theColorLeft: lda _tabLeftBlue,y: ldy _theColorRight: ora _tabRightBlue,y: ldy #200: sta (_wrtAdr),y:
            ldy _theColorLeft:ldx _theColorRight:
            lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #120: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #160: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #200: sta (_wrtAdr),y:
            lda _wrtAdr: clc: adc #240: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):
;; 1.3.4 DDAs STEP
            lda _dda1StepFunction : sta _myTmp : lda _dda1StepFunction+1 : sta _myTmp+1 :
            .( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :
            lda _dda3StepFunction : sta _myTmp : lda _dda3StepFunction+1 : sta _myTmp+1 :
        	.( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:
            :.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):
            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            :.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):


        dec _idxLin
        bmi endloopOnIdxLin_01
        jmp loopOnIdxLin_01
endloopOnIdxLin_01        
        ;; }

;; 1.4 INIT LOW LINES 
;; 1.4.1 INIT DDA COMMON
    ldy _idxCol:
    lda _tabMiddleX, y: sta _dda1StartValue: sta _dda1CurrentValue: lda _tabHighX, y: sta _dda1EndValue:
    lda _tabMiddleY, y: sta _dda2StartValue: sta _dda2CurrentValue: lda _tabHighY, y: sta _dda2EndValue: sec : sbc _dda2StartValue: sta _dda2NbVal:
    iny:
    lda _tabMiddleX, y: sta _dda3StartValue: sta _dda3CurrentValue: lda _tabHighX, y: sta _dda3EndValue:
    lda _tabMiddleY, y: sta _dda4StartValue: sta _dda4CurrentValue: lda _tabHighY, y: sta _dda4EndValue: sec : sbc _dda4StartValue: sta _dda4NbVal:
    lda #32:
    sta _dda2CurrentError:
    sta _dda4CurrentError:

;; 1.4.2 INIT DDA 1 SPECIFIC

    :.(:
    lda _dda1StartValue: cmp _dda1EndValue: bcs else:
        lda _dda1EndValue: sec: sbc _dda1StartValue: sta _dda1NbVal:
        lda #1: sta _dda1Increment:
    jmp endif:else:
        sbc _dda1EndValue: sta _dda1NbVal:
        lda #$FF: sta _dda1Increment:
    :endif:.):

    lda _dda1NbStep:
    cmp _dda1NbVal:
    beq NbStepEqualsNbVal_5678_00 :
    bcs NbStepGreaterThanNbVal_5678_00 :
        lda _dda1NbVal: sta _dda1CurrentError :
        lda #<(_dda1Step1ASM): sta _dda1StepFunction: lda #>(_dda1Step1ASM):sta _dda1StepFunction+1:
    jmp dda1InitDone_5678_00 :
    NbStepGreaterThanNbVal_5678_00    :
        lda _dda1NbStep: sta _dda1CurrentError:
        lda #<(_dda1Step2ASM): sta _dda1StepFunction: lda #>(_dda1Step2ASM): sta _dda1StepFunction+1:
    jmp dda1InitDone_5678_00 :
    NbStepEqualsNbVal_5678_00    :
        lda _dda1EndValue: sta _dda1CurrentError:
        lda #<(_dda1Step0ASM):sta _dda1StepFunction:lda #>(_dda1Step0ASM):sta _dda1StepFunction+1:
dda1InitDone_5678_00 :

;; 1.4.3  INIT DDA 3 SPECIFIC

    :.(:
    lda _dda3StartValue: cmp _dda3EndValue:bcs else:
        lda _dda3EndValue: sec: sbc _dda3StartValue: sta _dda3NbVal:
        lda #1: sta _dda3Increment:
    jmp endif: else:
        sbc _dda3EndValue: sta _dda3NbVal:
        lda #$FF: sta _dda3Increment:
    endif:.):

    lda _dda3NbStep:
    cmp _dda3NbVal:
    beq NbStepEqualsNbVal_8765_00:
    bcs NbStepGreaterThanNbVal_8765_00:
        lda _dda3NbVal: sta _dda3CurrentError:
        lda #<(_dda3Step1ASM): sta _dda3StepFunction: lda #>(_dda3Step1ASM): sta _dda3StepFunction+1:
    jmp dda3InitDone_8765_00:
    NbStepGreaterThanNbVal_8765_00    :
        lda _dda3NbStep: sta _dda3CurrentError:
        lda #<(_dda3Step2ASM): sta _dda3StepFunction: lda #>(_dda3Step2ASM): sta _dda3StepFunction+1:
    jmp dda3InitDone_8765_00:
    NbStepEqualsNbVal_8765_00    :
        lda _dda3EndValue: sta _dda3CurrentError:
        lda #<(_dda3Step0ASM): sta _dda3StepFunction: lda #>(_dda3Step0ASM): sta _dda3StepFunction+1:
dda3InitDone_8765_00:

;; 1.5 LOOP OVER LOW LINES
        ;; ==================
        lda #((SCREEN_HEIGHT/4)-1)
        sta _idxLin
        ;; for (idxLin=SCREEN_HEIGHT/2; idxLin< SCREEN_HEIGHT; idxLin+=2) {
loopOnIdxLin_02


;; 1.5.1 TOP PIXEL 
;; 1.5.1.1 TOP LEFT PIXEL COORDINATE 
;; 1.5.1.2 TOP LEFT PIXEL COLOR            
            lda _dda1CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda2CurrentValue: lda (_myTmp),y:
            sta _theColorLeft:
;; 1.5.1.3 TOP RIGHT PIXEL COORDINATE 
;; 1.5.1.4 TOP RIGHT PIXEL COLOR
            lda _dda3CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda4CurrentValue: lda (_myTmp),y:
            sta _theColorRight:
;; 1.5.1.5  WRITE TOP PIXEL ON SCREEN
            ldy _theColorLeft:ldx _theColorRight:
            lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #0: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #40: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #80: sta (_wrtAdr),y:
;; 1.5.2 DDAs STEP
            lda _dda1StepFunction : sta _myTmp : lda _dda1StepFunction+1 : sta _myTmp+1 :
            .( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :
            lda _dda3StepFunction : sta _myTmp : lda _dda3StepFunction+1 : sta _myTmp+1 :
        	.( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:
            :.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):
            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            :.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):
;; 1.5.3 BOTTOM PIXEL 
;; 1.5.3.1 BOTTOM LEFT PIXEL COORDINATE 
;; 1.5.3.2 BOTTOM LEFT PIXEL COLOR
            lda _dda1CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda2CurrentValue: lda (_myTmp),y:
            sta _theColorLeft:
;; 1.5.3.3 BOTTOM RIGHT PIXEL COORDINATE
;; 1.5.3.4 BOTTOM RIGHT PIXEL COLOR
            lda _dda3CurrentValue: clc: adc _rollCoord: tay:
            lda _adrTextureLow,y:sta _myTmp:lda _adrTextureHigh,y:sta _myTmp+1:
            ldy _dda4CurrentValue: lda (_myTmp),y:
            sta _theColorRight:
;; 1.5.3.5 WRITE BOTTOM PIXEL ON SCREEN
            ldy _theColorLeft:ldx _theColorRight:
            lda _tabLeftRed,y:   ora _tabRightRed,x: ldy #120: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftGreen,y: ora _tabRightGreen,x: ldy #160: sta (_wrtAdr),y:
            ldy _theColorLeft: lda _tabLeftBlue,y:  ora _tabRightBlue,x: ldy #200: sta (_wrtAdr),y:
            lda _wrtAdr: clc: adc #240: sta _wrtAdr: .(: bcc skip:    inc _wrtAdr+1: skip: .):
;; 1.5.4 DDAs STEP
            lda _dda1StepFunction : sta _myTmp : lda _dda1StepFunction+1 : sta _myTmp+1 :
            .( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :
            lda _dda3StepFunction : sta _myTmp : lda _dda3StepFunction+1 : sta _myTmp+1 :
        	.( : lda _myTmp : sta call+1: lda _myTmp+1 : sta call+2 : ldy #0 :call : jsr 0000 : .) :            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            lda _dda2CurrentError: sec: sbc _dda2NbVal: sta _dda2CurrentError:
            :.(:bmi updateError: asl: cmp _dda2NbStep: bcs  done :updateError: lda _dda2CurrentError: clc: adc _dda2NbStep: sta _dda2CurrentError: inc _dda2CurrentValue: done:.):
            lda _dda4CurrentError: sec: sbc _dda4NbVal: sta _dda4CurrentError:
            :.(:bmi updateError: asl: cmp _dda4NbStep: bcs  done :updateError: lda _dda4CurrentError: clc: adc _dda4NbStep: sta _dda4CurrentError: inc _dda4CurrentValue: done:.):

        dec _idxLin
        bmi endloopOnIdxLin_02
        jmp loopOnIdxLin_02
endloopOnIdxLin_02
        ;; }

;; 1.6 NEXT COL
    lda _theBaseAdr: clc: adc #1: sta _theBaseAdr :.(: bcc skip:    inc _theBaseAdr+1: skip: .)

    inc _idxCol
    inc _idxCol
    lda _idxCol
    cmp #(SCREEN_WIDTH)
    beq endLoopOnIdxCol_01
    jmp loopOnIdxCol_01
endLoopOnIdxCol_01
    ;; } end for
project2ScreenPureASM_done
.)
    rts

#endif // __USE_C_DDA__