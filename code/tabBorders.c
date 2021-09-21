
#define NB_VAL 78


unsigned char tabLowX[NB_VAL];
unsigned char tabMiddleX[NB_VAL];
unsigned char tabHighX[NB_VAL];
unsigned char tabLowY[NB_VAL];
unsigned char tabMiddleY[NB_VAL];
unsigned char tabHighY[NB_VAL];
unsigned char idxColumn;

unsigned char tabBorderX_01[] = {
	109, 110, 110, 110, 111, 111, 112, 112, 113, 113, 113, 114, 114, 115, 115, 116
	, 116, 117, 117, 118, 118, 119, 119, 120, 120, 121, 121, 122, 122, 123, 123, 124
	, 124, 125, 125, 126, 126, 127, 127, 128, 129, 129, 130, 130, 131, 131, 132, 132
	, 133, 133, 134, 134, 135, 135, 136, 136, 137, 137, 138, 138, 139, 139, 140, 140
	, 141, 141, 142, 142, 143, 143, 143, 144, 144, 145, 145, 146, 146, 146};

unsigned char tabBorderX_02[] = {
	104, 104, 105, 105, 106, 106, 107, 108, 108, 109, 109, 110, 110, 111, 112, 112
	, 113, 114, 114, 115, 115, 116, 116, 117, 118, 118, 119, 120, 120, 121, 122, 122
	, 123, 124, 125, 125, 126, 127, 127, 128, 129, 129, 130, 131, 131, 132, 133, 134
	, 134, 135, 136, 136, 137, 138, 138, 139, 140, 140, 141, 141, 142, 142, 143, 144
	, 144, 145, 146, 146, 147, 147, 148, 148, 149, 150, 150, 151, 151, 152};

unsigned char tabBorderX_03[] = {
	92, 92, 93, 93, 94, 94, 95, 96, 96, 97, 98, 98, 99, 100, 101, 101
	, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 116, 116, 118
	, 119, 120, 122, 123, 124, 125, 127, 128, 129, 131, 132, 133, 134, 136, 137, 138
	, 140, 140, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155
	, 155, 156, 157, 158, 158, 159, 160, 160, 161, 162, 162, 163, 163, 164};

unsigned char tabBorderX_04[] = {
	64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65
	, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 68
	, 68, 69, 70, 72, 74, 78, 88, 128, 168, 178, 182, 184, 186, 187, 188, 188
	, 189, 189, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 191
	, 191, 191, 191, 191, 191, 191, 191, 191, 192, 192, 192, 192, 192, 192};

unsigned char tabBorderY_01[] = {
	18, 17, 17, 16, 16, 16, 15, 15, 14, 14, 13, 13, 13, 12, 12, 11
	, 11, 10, 10, 9, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4
	, 3, 3, 2, 2, 1, 1, 1, 0, 1, 1, 1, 2, 2, 3, 3, 4
	, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11, 11
	, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 16, 17, 17};

unsigned char tabBorderY_02[] = {
	24, 24, 24, 23, 22, 22, 22, 22, 22, 22, 21, 21, 20, 20, 20, 20
	, 20, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 17, 17
	, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17
	, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 20, 20
	, 20, 20, 20, 21, 21, 22, 22, 22, 22, 22, 22, 23, 24, 24};

unsigned char tabBorderY_03[] = {
	36, 36, 35, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 34, 34
	, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 32, 32, 32, 32, 32
	, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
	, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34
	, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 36};

unsigned char tabBorderY_04[] = {
	50, 50, 50, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49
	, 49, 49, 49, 49, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48
	, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48
	, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49
	, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50};

unsigned char tabBorderY_05[] = {
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
	, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64};


void selectTables(){


    switch (rotX) {
        case 0:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_01[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_01[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_01[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_04[idxColumn];
                tabMiddleY[idxColumn]  = tabBorderY_05[idxColumn];
                tabHighY[idxColumn]    = 128-tabBorderY_04[idxColumn];   
            }
            break;
        case ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_01[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_01[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_02[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_05[idxColumn];
                tabMiddleY[idxColumn]  = 128-tabBorderY_04[idxColumn];
                tabHighY[idxColumn]    = 128-tabBorderY_03[idxColumn];   
            }
            break;
        case 2*ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_01[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_02[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_03[idxColumn] - rotZ;
                tabLowY[idxColumn]     = 128 - tabBorderY_04[idxColumn];
                tabMiddleY[idxColumn]  = 128 - tabBorderY_03[idxColumn];
                tabHighY[idxColumn]    = 128 - tabBorderY_02[idxColumn];   
            }
            break;
        // case 3*ANGLE_INCREMENT:
        //     for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
        //         tabLowX[idxColumn]     = tabBorderX_02[idxColumn] - rotZ;
        //         tabMiddleX[idxColumn]  = tabBorderX_03[idxColumn] - rotZ;
        //         tabHighX[idxColumn]    = tabBorderX_04[idxColumn] - rotZ;
        //         tabLowY[idxColumn]     = 128 - tabBorderY_03[idxColumn];
        //         tabMiddleY[idxColumn]  = 128 - tabBorderY_02[idxColumn];
        //         tabHighY[idxColumn]    = 128 - tabBorderY_01[idxColumn];   
        //     }
        //     break;
        case -1*ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_02[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_01[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_01[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_03[idxColumn];
                tabMiddleY[idxColumn]  = tabBorderY_04[idxColumn];
                tabHighY[idxColumn]    = tabBorderY_05[idxColumn];   
            }
            break;
        case -2*ANGLE_INCREMENT:
            for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
                tabLowX[idxColumn]     = tabBorderX_03[idxColumn] - rotZ;
                tabMiddleX[idxColumn]  = tabBorderX_02[idxColumn] - rotZ;
                tabHighX[idxColumn]    = tabBorderX_01[idxColumn] - rotZ;
                tabLowY[idxColumn]     = tabBorderY_02[idxColumn];
                tabMiddleY[idxColumn]  = tabBorderY_03[idxColumn];
                tabHighY[idxColumn]    = tabBorderY_04[idxColumn];   
            }
            break;
        // case -3*ANGLE_INCREMENT:
        //     for (idxColumn=0; idxColumn<NB_VAL; idxColumn++) {
        //         tabLowX[idxColumn]     = tabBorderX_04[idxColumn] - rotZ;
        //         tabMiddleX[idxColumn]  = tabBorderX_03[idxColumn] - rotZ;
        //         tabHighX[idxColumn]    = tabBorderX_02[idxColumn] - rotZ;
        //         tabLowY[idxColumn]     = tabBorderY_01[idxColumn];
        //         tabMiddleY[idxColumn]  = tabBorderY_02[idxColumn];
        //         tabHighY[idxColumn]    = tabBorderY_03[idxColumn];   
        //     }
        //     break;
        // default:
        //     break;
    }
    if ((abs(rotZ)) > 4*ANGLE_INCREMENT) {
        for (idxColumn=0; idxColumn<NB_VAL; idxColumn++){
            tabLowX[idxColumn]     +=128;
            tabMiddleX[idxColumn]  +=128;
            tabHighX[idxColumn]    +=128;
        }
    }
}
