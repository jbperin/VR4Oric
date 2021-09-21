#include <stdio.h>

#define ANGLE_INCREMENT 16
#define abs(x)          (((x)<0)?-(x):(x))

signed char rotZ;
signed char rotX;

#include "tabBorders.c"


void main (){
    printf ("debut\n");
    rotZ = 7*ANGLE_INCREMENT;
    rotX = -1*ANGLE_INCREMENT;
    selectTables();
    printf ("fin\n");
}
