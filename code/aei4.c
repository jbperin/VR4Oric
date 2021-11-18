
#ifdef __GNUC__
unsigned char   dda4NbStep;
unsigned char   dda4StartValue;
unsigned char   dda4CurrentValue;
unsigned char   dda4EndValue;
unsigned char   dda4NbVal;
signed char     dda4CurrentError;

#else
extern unsigned char   dda4NbStep;
extern unsigned char   dda4StartValue;

extern unsigned char   dda4CurrentValue;
extern unsigned char   dda4EndValue;
extern unsigned char   dda4NbVal;
extern signed char     dda4CurrentError;
#endif
void            (*dda4StepFunction)(); 

#ifdef __USE_C_DDA__

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

#endif // __USE_C_DDA__
