
#include <stdio.h>

unsigned char   dda1NbStep;
unsigned char   dda1StartValue;

unsigned char   dda1CurrentValue;
unsigned char   dda1EndValue;
unsigned char   dda1NbVal;
signed char     dda1CurrentError;
void            (*dda1StepFunction)(); 
signed char     dda1Increment;

void dda1Step0(){

    dda1CurrentValue         += dda1Increment;
 
}

void dda1Step1(){

    while ((dda1CurrentError<<1) >= dda1NbStep) {
        dda1CurrentError         -= dda1NbStep;
        dda1CurrentValue         += dda1Increment;
    }
    dda1CurrentError     += dda1NbVal;
  
}
void dda1Step2(){

    dda1CurrentError         -= dda1NbVal; // dda1EndValue-dda1StartValue;
    if ((dda1CurrentError<<1) < dda1NbStep) {
        dda1CurrentError     += dda1NbStep;
        dda1CurrentValue     += dda1Increment;
    }

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