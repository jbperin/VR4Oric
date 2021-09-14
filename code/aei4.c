
// #include <stdio.h>

unsigned char   dda4NbStep;
unsigned char   dda4StartValue;

unsigned char   dda4CurrentValue;
unsigned char   dda4EndValue;
unsigned char   dda4NbVal;
signed char     dda4CurrentError;
void            (*dda4StepFunction)(); 
signed char     dda4Increment;

void dda4Step0(){

    dda4CurrentValue         += dda4Increment;
 
}

void dda4Step1(){

    while ((dda4CurrentError<<1) >= dda4NbStep) {
        dda4CurrentError         -= dda4NbStep;
        dda4CurrentValue         += dda4Increment;
    }
    dda4CurrentError     += dda4NbVal;
  
}
void dda4Step2(){

    dda4CurrentError         -= dda4NbVal; // dda4EndValue-dda4StartValue;
    if ((dda4CurrentError<<1) < dda4NbStep) {
        dda4CurrentError     += dda4NbStep;
        dda4CurrentValue     += dda4Increment;
    }

}

void dda4Init(){

    dda4CurrentValue         = dda4StartValue;

    if (dda4EndValue > dda4StartValue) {
        dda4NbVal                = dda4EndValue-dda4StartValue;
        dda4Increment            = 1;
    } else {
        dda4NbVal                = dda4StartValue-dda4EndValue;
        dda4Increment            = -1;
    }
    //dda4EndValue             = dda4StartValue + dda4NbVal;

    if          (dda4NbVal > dda4NbStep) {
        dda4CurrentError     = dda4NbVal;
        dda4StepFunction     = &dda4Step1;
    } else if   (dda4NbVal < dda4NbStep) {
        dda4CurrentError     = dda4NbStep;
        dda4StepFunction     = &dda4Step2;
    } else {
        dda4CurrentError     = dda4EndValue;
        dda4StepFunction     = &dda4Step0;
    }

}

