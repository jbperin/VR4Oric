
// #include <stdio.h>

extern unsigned char   dda2NbStep;
extern unsigned char   dda2StartValue;

extern unsigned char   dda2CurrentValue;
extern unsigned char   dda2EndValue;
extern unsigned char   dda2NbVal;
extern signed char     dda2CurrentError;
void            (*dda2StepFunction)(); 


#ifdef __USE_C_DDA__

// void dda2Step2(){

//     dda2CurrentError         -= dda2NbVal; // dda2EndValue-dda2StartValue;
//     if ((dda2CurrentError<<1) < dda2NbStep) {
//         dda2CurrentError     += dda2NbStep;
//         dda2CurrentValue     ++;
//     }

// }

// void dda2Init(){

//     dda2CurrentValue         = dda2StartValue;

//     // if (dda2EndValue > dda2StartValue) {
//     dda2NbVal                = dda2EndValue-dda2StartValue;
//     // } else {
//     //     dda2NbVal                = dda2StartValue-dda2EndValue;
//     //     dda2Increment            = -1;
//     // }
//     //dda2EndValue             = dda2StartValue + dda2NbVal;

//     // if          (dda2NbVal > dda2NbStep) {
//     //     dda2CurrentError     = dda2NbVal;
//     //     dda2StepFunction     = &dda2Step1;
//     // } else if   (dda2NbVal < dda2NbStep) {
//         dda2CurrentError     = dda2NbStep;
//         dda2StepFunction     = &dda2Step2;
//     // } else {
//     //     dda2CurrentError     = dda2EndValue;
//     //     dda2StepFunction     = &dda2Step0;
//     // }

// }
#endif
