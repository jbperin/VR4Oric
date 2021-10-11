
.zero

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


; unsigned char   ddaNbStep;
; unsigned char   ddaStartValue;
; unsigned char   ddaCurrentValue;
; unsigned char   ddaEndValue;
; unsigned char   ddaNbVal;
; signed char     ddaCurrentError;
; void            (*ddaStepFunction)(); 
; signed char     ddaIncrement;
; void ddaInit(){
; 
;     ddaCurrentValue         = ddaStartValue;
; 
;     if (ddaEndValue > ddaStartValue) {
;         ddaNbVal                = ddaEndValue-ddaStartValue;
;         ddaIncrement            = 1;
;     } else {
;         ddaNbVal                = ddaStartValue-ddaEndValue;
;         ddaIncrement            = -1;
;     }
;     //ddaEndValue             = ddaStartValue + ddaNbVal;
; 
;     if          (ddaNbVal > ddaNbStep) {
;         ddaCurrentError     = ddaNbVal;
;         ddaStepFunction     = &ddaStep1;
;     } else if   (ddaNbVal < ddaNbStep) {
;         ddaCurrentError     = ddaNbStep;
;         ddaStepFunction     = &ddaStep2;
;     } else {
;         ddaCurrentError     = ddaEndValue;
;         ddaStepFunction     = &ddaStep0;
;     }
; 
; }
; void ddaStep0(){
;     ddaCurrentValue         += ddaIncrement;
; }
; void ddaStep1(){
;     while ((ddaCurrentError<<1) >= ddaNbStep) {
;         ddaCurrentError         -= ddaNbStep;
;         ddaCurrentValue         += ddaIncrement;
;     }
;     ddaCurrentError     += ddaNbVal;
; }
; void ddaStep2(){
;     ddaCurrentError         -= ddaNbVal;
;     if ((ddaCurrentError<<1) < ddaNbStep) {
;         ddaCurrentError     += ddaNbStep;
;         ddaCurrentValue     += ddaIncrement;
;     }
; }

.text

_dda1Step0ASM
.(
    ;; TODO: OPTIM: replace by patch inc/dec instruction
    lda         _dda1CurrentValue
    clc
    adc         _dda1Increment
    sta         _dda1CurrentValue
.)
    rts


_dda1Step1ASM
.(
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
            ;; TODO: OPTIM: replace by patch inc/dec instruction
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



_dda1Step2ASM
.(
    lda         _dda1CurrentError
    sec
    sbc         _dda1NbVal
    sta         _dda1CurrentError
    bmi         updateError
    asl
    cmp         _dda1NbStep
    bcc         updateError
    rts
updateError
            lda         _dda1CurrentError
            clc
            adc         _dda1NbStep
            sta         _dda1CurrentError
            ;; TODO: OPTIM: replace by patch inc/dec instruction
            lda         _dda1CurrentValue
            clc
            adc         _dda1Increment
            sta         _dda1CurrentValue
.)
    rts

_dda3Step0ASM
.(
    lda         _dda3CurrentValue
    clc
    adc         _dda3Increment
    sta         _dda3CurrentValue
.)
    rts

_dda3Step1ASM
.(
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
            ;; TODO: OPTIM: replace by patch inc/dec instruction
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


_dda3Step2ASM
.(
    lda         _dda3CurrentError
    sec
    sbc         _dda3NbVal
    sta         _dda3CurrentError
    bmi         updateError
    asl
    cmp         _dda3NbStep
    bcc         updateError
    rts
updateError
            lda         _dda3CurrentError
            clc
            adc         _dda3NbStep
            sta         _dda3CurrentError
            ;; TODO: OPTIM: replace by patch inc/dec instruction
            lda _dda3CurrentValue:clc: adc _dda3Increment: sta _dda3CurrentValue
.)
    rts

