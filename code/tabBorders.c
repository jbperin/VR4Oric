
#define NB_VAL 78

unsigned char tabLowX[NB_VAL];
unsigned char tabMiddleX[NB_VAL];
unsigned char tabHighX[NB_VAL];
unsigned char tabLowY[NB_VAL];
unsigned char tabMiddleY[NB_VAL];
unsigned char tabHighY[NB_VAL];

unsigned char idxColumn;

#ifndef __GNUC__
unsigned char *tabBorderX_01 = borderTables;
unsigned char *tabBorderX_02 = borderTables + 1*NB_VAL;
unsigned char *tabBorderX_03 = borderTables + 2*NB_VAL;
unsigned char *tabBorderX_04 = borderTables + 3*NB_VAL;
unsigned char *tabBorderX_05 = borderTables + 4*NB_VAL;
unsigned char *tabBorderY_01 = borderTables + 5*NB_VAL;
unsigned char *tabBorderY_02 = borderTables + 6*NB_VAL;
unsigned char *tabBorderY_03 = borderTables + 7*NB_VAL;
unsigned char *tabBorderY_04 = borderTables + 8*NB_VAL;
unsigned char *tabBorderY_05 = borderTables + 9*NB_VAL;
unsigned char *tabBorderY_06 = borderTables + 10*NB_VAL;
unsigned char *tabBorderY_07 = borderTables + 11*NB_VAL;
unsigned char *tabBorderY_08 = borderTables + 12*NB_VAL;


#else
unsigned char tabBorderX_01[] = {
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66
	, 66, 66, 67, 68, 68, 71, 76, 128, 180, 185, 188, 188, 189, 190, 190, 190
	, 190, 190, 190, 191, 191, 191, 191, 191, 191, 191, 191, 192, 192, 192, 192, 192
	, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192};

unsigned char tabBorderX_02[] = {
	85, 86, 86, 87, 87, 88, 88, 89, 90, 90, 91, 92, 92, 93, 94, 95
	, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 107, 108, 110, 111, 113, 114
	, 116, 117, 119, 121, 123, 124, 126, 128, 130, 132, 133, 135, 137, 139, 140, 142
	, 143, 145, 146, 148, 149, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161
	, 162, 163, 164, 164, 165, 166, 166, 167, 168, 168, 169, 169, 170, 170};

unsigned char tabBorderX_03[] = {
	81, 82, 82, 82, 83, 84, 84, 84, 85, 86, 86, 87, 88, 88, 89, 90
	, 90, 92, 92, 94, 94, 96, 96, 98, 99, 100, 102, 104, 105, 107, 108, 110
	, 112, 114, 117, 119, 121, 123, 126, 128, 130, 133, 135, 137, 139, 142, 144, 146
	, 148, 149, 151, 152, 154, 156, 157, 158, 160, 160, 162, 162, 164, 164, 166, 166
	, 167, 168, 168, 169, 170, 170, 171, 172, 172, 172, 173, 174, 174, 174};

unsigned char tabBorderX_04[] = {
	98, 99, 99, 100, 100, 101, 102, 102, 103, 103, 104, 104, 105, 106, 106, 108
	, 108, 109, 110, 110, 111, 112, 112, 114, 114, 116, 116, 117, 118, 118, 120, 120
	, 122, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 134, 136
	, 136, 138, 138, 139, 140, 140, 142, 142, 144, 144, 145, 146, 146, 147, 148, 148
	, 150, 150, 151, 152, 152, 153, 153, 154, 154, 155, 156, 156, 157, 157};

unsigned char tabBorderX_05[] = {
	91, 92, 92, 93, 94, 94, 95, 95, 96, 97, 97, 98, 99, 100, 100, 101
	, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 116, 117, 118
	, 119, 120, 122, 123, 124, 125, 127, 128, 129, 131, 132, 133, 134, 136, 137, 138
	, 139, 140, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155
	, 156, 156, 157, 158, 159, 159, 160, 161, 161, 162, 162, 163, 164, 164};

unsigned char tabBorderY_01[] = {
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};

unsigned char tabBorderY_02[] = {
	41, 41, 40, 40, 40, 40, 39, 39, 39, 38, 38, 38, 37, 37, 37, 37
	, 36, 36, 36, 35, 35, 35, 35, 34, 34, 34, 34, 33, 33, 33, 33, 33
	, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33
	, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 37
	, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 40, 41};

unsigned char tabBorderY_03[] = {
	75, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77
	, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79
	, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79
	, 79, 79, 79, 79, 79, 79, 79, 78, 78, 78, 78, 78, 78, 78, 78, 77
	, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 76, 76, 76};

unsigned char tabBorderY_04[] = {
	54, 54, 54, 54, 53, 53, 53, 53, 53, 52, 52, 52, 52, 52, 52, 51
	, 51, 51, 51, 51, 50, 50, 50, 50, 50, 49, 49, 49, 49, 49, 49, 49
	, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49
	, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51
	, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 54, 54, 54};

unsigned char tabBorderY_05[] = {
	32, 32, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, 25
	, 25, 24, 24, 23, 22, 22, 21, 21, 20, 20, 19, 19, 19, 18, 18, 17
	, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17
	, 18, 18, 19, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25, 25
	, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32};

unsigned char tabBorderY_06[] = {
	64, 64, 64, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
	, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
	, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
	, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
	, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64};

unsigned char tabBorderY_07[] = {
	45, 45, 44, 44, 44, 43, 43, 43, 42, 42, 42, 41, 41, 40, 40, 40
	, 39, 39, 38, 38, 37, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33
	, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33
	, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 37, 38, 38, 39, 39, 40
	, 40, 40, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 44, 45};

unsigned char tabBorderY_08[] = {
	29, 28, 28, 27, 27, 26, 26, 25, 24, 24, 23, 23, 22, 21, 21, 20
	, 19, 18, 18, 17, 16, 15, 15, 14, 13, 12, 11, 11, 10, 9, 8, 7
	, 6, 5, 4, 4, 3, 2, 1, 0, 1, 2, 3, 4, 4, 5, 6, 7
	, 8, 9, 10, 11, 11, 12, 13, 14, 15, 15, 16, 17, 18, 18, 19, 20
	, 21, 21, 22, 23, 23, 24, 24, 25, 26, 26, 27, 27, 28, 28};
#endif

void selectTables(){


    switch (rotX) {
        case 0:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_05[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_05[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_05[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_02[idxColumn];
                tabMiddleY[idxColumn]  = tabBorderY_01[idxColumn];
                tabHighY[idxColumn]    = 128-tabBorderY_02[idxColumn];   
            }
            break;
        case ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_04[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_05[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_03[idxColumn] - rotZ;
                tabLowY[idxColumn]     = 128-tabBorderY_03[idxColumn];
                tabMiddleY[idxColumn]  = 128-tabBorderY_04[idxColumn];
                tabHighY[idxColumn]    = 128-tabBorderY_05[idxColumn];   
            }
            break;
        case 2*ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_04[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_02[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_01[idxColumn] - rotZ;
                tabLowY[idxColumn]     = 128 - tabBorderY_06[idxColumn];
                tabMiddleY[idxColumn]  = 128 - tabBorderY_07[idxColumn];
                tabHighY[idxColumn]    = 128 - tabBorderY_08[idxColumn];   
            }
            break;
        case -1*ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_03[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_05[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_04[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_05[idxColumn];
                tabMiddleY[idxColumn]  = tabBorderY_04[idxColumn];
                tabHighY[idxColumn]    = tabBorderY_03[idxColumn];   
            }
            break;
        case -2*ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_01[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_02[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_04[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_08[idxColumn];
                tabMiddleY[idxColumn]  = tabBorderY_07[idxColumn];
                tabHighY[idxColumn]    = tabBorderY_06[idxColumn];   
            }
            break;
        default:
            break;
    }
    if (rollCoord) {
        for (idxColumn=0; idxColumn<NB_VAL; idxColumn++){
            tabLowX[idxColumn]     +=128;
            tabMiddleX[idxColumn]  +=128;
            tabHighX[idxColumn]    +=128;
        }
    }
}
