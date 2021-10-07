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
#endif // __USE_C_DDA__