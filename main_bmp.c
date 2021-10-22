#include "bmp_management.h"

int main(){

    PixelDataElement p1 = {0,1,2};
    PixelDataElement p2 = {3,4,5};
    PixelDataElement p3 = {6,7,8};
    PixelDataElement l1[3] = {p1,p2,p3};
    PixelDataElement p4 = {9,10,11};
    PixelDataElement p5 = {0,255,0};
    PixelDataElement p6 = {15,16,17};
    PixelDataElement l2[3] = {p4,p5,p6};
    PixelDataElement p7 = {18,19,20};
    PixelDataElement p8 = {21,22,23};
    PixelDataElement p9 = {24,25,26};
    PixelDataElement l3[3] = {p7,p8,p9};
    
    PixelDataElement * pTab[3] = {l1,l2,l3};
   
    BMP_256_printMatrix(pTab,3,3,"new_test.bmp");
    
    return 0;
}
