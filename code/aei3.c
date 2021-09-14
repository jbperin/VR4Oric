
// #include <stdio.h>

unsigned char   dda3NbStep;
unsigned char   dda3StartValue;

unsigned char   dda3CurrentValue;
unsigned char   dda3EndValue;
unsigned char   dda3NbVal;
signed char     dda3CurrentError;
void            (*dda3StepFunction)(); 
signed char     dda3Increment;

void dda3Step0(){

    dda3CurrentValue         += dda3Increment;
 
}

void dda3Step1(){

    while ((dda3CurrentError<<1) >= dda3NbStep) {
        dda3CurrentError         -= dda3NbStep;
        dda3CurrentValue         += dda3Increment;
    }
    dda3CurrentError     += dda3NbVal;
  
}
void dda3Step2(){

    dda3CurrentError         -= dda3NbVal; // dda3EndValue-dda3StartValue;
    if ((dda3CurrentError<<1) < dda3NbStep) {
        dda3CurrentError     += dda3NbStep;
        dda3CurrentValue     += dda3Increment;
    }

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

// void main () {
//     printf ("coucou\n");

//     dda3StartValue       = 30;
//     dda3EndValue         = 7;

//     dda3NbStep           = 5;

//     dda3Init();
//     printf ("%d\n", dda3CurrentValue);
//     while (dda3CurrentValue != dda3EndValue) {
//         (*dda3StepFunction)(); 
//         printf ("%d\n", dda3CurrentValue);
//     }

// }