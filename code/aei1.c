
// #include <stdio.h>
#include "config.h"


#ifdef __GNUC__
unsigned char   dda1NbStep;
unsigned char   dda1StartValue;
unsigned char   dda1CurrentValue;
unsigned char   dda1EndValue;
unsigned char   dda1NbVal;
signed char     dda1CurrentError;
signed char     dda1Increment;

#else
extern unsigned char   dda1NbStep;
extern unsigned char   dda1StartValue;

extern unsigned char   dda1CurrentValue;
extern unsigned char   dda1EndValue;
extern unsigned char   dda1NbVal;
extern signed char     dda1CurrentError;
extern signed char     dda1Increment;
#endif
void            (*dda1StepFunction)(); 

#ifdef __USE_C_DDA__
void dda1Step0(){

    dda1CurrentValue         += dda1Increment;
    // asm ("lda _dda1CurrentValue: clc: adc _dda1Increment: sta _dda1CurrentValue");
    // dda1Step0ASM();
}

void dda1Step1(){

    while ((dda1CurrentError<<1) >= dda1NbStep) {
        dda1CurrentError         -= dda1NbStep;
        dda1CurrentValue         += dda1Increment;
    }
    dda1CurrentError     += dda1NbVal;

    // asm (
    //     ":.(:loop:"
    //     ":lda _dda1CurrentError:bmi end_loop: asl: cmp _dda1NbStep: bcc end_loop:"
    //     ":lda _dda1CurrentError: sec: sbc _dda1NbStep: sta _dda1CurrentError: lda _dda1CurrentValue: clc: adc _dda1Increment: sta _dda1CurrentValue:"
    //     ":jmp loop:"
    //     ":end_loop:.):"
    //     ":lda _dda1CurrentError: clc: adc _dda1NbVal: sta _dda1CurrentError"
    // );  
    // dda1Step1ASM();
}
void dda1Step2(){

    dda1CurrentError         -= dda1NbVal; // dda1EndValue-dda1StartValue;
    if ((dda1CurrentError<<1) < dda1NbStep) {
        dda1CurrentError     += dda1NbStep;
        dda1CurrentValue     += dda1Increment;
    }
    // asm(
    //     "lda _dda1CurrentError: sec: sbc _dda1NbVal: sta _dda1CurrentError:"
    //     ":.(:bmi updateError: asl: cmp _dda1NbStep: bcs  done :updateError: lda _dda1CurrentError: clc: adc _dda1NbStep: sta _dda1CurrentError: lda _dda1CurrentValue: clc: adc _dda1Increment: sta _dda1CurrentValue: done:.):"
    // );
    // dda1Step2ASM();
}

void dda1Init(){

    dda1CurrentValue         = dda1StartValue;

    if (dda1EndValue > dda1StartValue) {
        dda1NbVal                = dda1EndValue-dda1StartValue;
        dda1Increment            = 1;
    } else {
        dda1NbVal                = dda1StartValue-dda1EndValue;
        dda1Increment            = -1;
    }
    //dda1EndValue             = dda1StartValue + dda1NbVal;

    if          (dda1NbVal > dda1NbStep) {
        dda1CurrentError     = dda1NbVal;
        dda1StepFunction     = &dda1Step1;
    } else if   (dda1NbVal < dda1NbStep) {
        dda1CurrentError     = dda1NbStep;
        dda1StepFunction     = &dda1Step2;
    } else {
        dda1CurrentError     = dda1EndValue;
        dda1StepFunction     = &dda1Step0;
    }

}
#endif // __USE_C_DDA__

// void main () {
//     printf ("coucou\n");

//     dda1StartValue       = 30;
//     dda1EndValue         = 7;

//     dda1NbStep           = 5;

//     dda1Init();
//     printf ("%d\n", dda1CurrentValue);
//     while (dda1CurrentValue != dda1EndValue) {
//         (*dda1StepFunction)(); 
//         printf ("%d\n", dda1CurrentValue);
//     }

// }