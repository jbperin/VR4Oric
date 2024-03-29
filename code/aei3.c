
// #include <stdio.h>
#include "config.h"

#ifdef __GNUC__
unsigned char   dda3NbStep;
unsigned char   dda3StartValue;
unsigned char   dda3CurrentValue;
unsigned char   dda3EndValue;
unsigned char   dda3NbVal;
signed char     dda3CurrentError;
signed char     dda3Increment;
#else
extern unsigned char   dda3NbStep;
extern unsigned char   dda3StartValue;
extern unsigned char   dda3CurrentValue;
extern unsigned char   dda3EndValue;
extern unsigned char   dda3NbVal;
extern signed char     dda3CurrentError;
extern signed char     dda3Increment;
#endif
void                   (*dda3StepFunction)(); 


#ifdef __USE_C_DDA__

void dda3Step0(){

    dda3CurrentValue         += dda3Increment;
    // asm ("lda _dda3CurrentValue: clc: adc _dda3Increment: sta _dda3CurrentValue");

}

void dda3Step1(){

    while ((dda3CurrentError<<1) >= dda3NbStep) {
        dda3CurrentError         -= dda3NbStep;
        dda3CurrentValue         += dda3Increment;
    }
    dda3CurrentError     += dda3NbVal;
    // asm (
    //     ":.(:loop:"
    //     ":lda _dda3CurrentError:bmi end_loop: asl: cmp _dda3NbStep: bcc end_loop:"
    //     ":lda _dda3CurrentError: sec: sbc _dda3NbStep: sta _dda3CurrentError: lda _dda3CurrentValue: clc: adc _dda3Increment: sta _dda3CurrentValue:"
    //     ":jmp loop:"
    //     ":end_loop:.):"
    //     ":lda _dda3CurrentError: clc: adc _dda3NbVal: sta _dda3CurrentError"
    // );
}
void dda3Step2(){

    dda3CurrentError         -= dda3NbVal; // dda3EndValue-dda3StartValue;
    if ((dda3CurrentError<<1) < dda3NbStep) {
        dda3CurrentError     += dda3NbStep;
        dda3CurrentValue     += dda3Increment;
    }
    // asm(
    //     "lda _dda3CurrentError: sec: sbc _dda3NbVal: sta _dda3CurrentError:"
    //     ":.(:bmi updateError: asl: cmp _dda3NbStep: bcs  done :updateError: lda _dda3CurrentError: clc: adc _dda3NbStep: sta _dda3CurrentError: lda _dda3CurrentValue:clc: adc _dda3Increment: sta _dda3CurrentValue: done:.):"
    // );
}

void dda3Init(){

    dda3CurrentValue         = dda3StartValue;

    if (dda3EndValue > dda3StartValue) {
        dda3NbVal                = dda3EndValue-dda3StartValue;
        dda3Increment            = 1;
    } else {
        dda3NbVal                = dda3StartValue-dda3EndValue;
        dda3Increment            = -1;
    }
    //dda3EndValue             = dda3StartValue + dda3NbVal;

    if          (dda3NbVal > dda3NbStep) {
        dda3CurrentError     = dda3NbVal;
        dda3StepFunction     = &dda3Step1;
    } else if   (dda3NbVal < dda3NbStep) {
        dda3CurrentError     = dda3NbStep;
        dda3StepFunction     = &dda3Step2;
    } else {
        dda3CurrentError     = dda3EndValue;
        dda3StepFunction     = &dda3Step0;
    }

}
#endif // __USE_C_DDA__

