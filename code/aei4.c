

unsigned char   dda4NbStep;
unsigned char   dda4StartValue;

unsigned char   dda4CurrentValue;
unsigned char   dda4EndValue;
unsigned char   dda4NbVal;
signed char     dda4CurrentError;
void            (*dda4StepFunction)(); 


void dda4Step2(){

    dda4CurrentError         -= dda4NbVal; 
    if ((dda4CurrentError<<1) < dda4NbStep) {
        dda4CurrentError     += dda4NbStep;
        dda4CurrentValue     ++;
    }

}

void dda4Init(){

    dda4CurrentValue         = dda4StartValue;
    dda4NbVal                = dda4EndValue-dda4StartValue;
    dda4CurrentError     = dda4NbStep;
    dda4StepFunction     = &dda4Step2;

}

