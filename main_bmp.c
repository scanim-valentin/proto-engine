#include "bmp_management.h"
#include <stdio.h>

int main(){

    Header theHeader = {0x4C42,BMP_size(9),0,0};
    printf("Taille du fichier = %u\n",BMP_size(9));
    InfoHeader theInfoHeader = {40,3,3,1,24,0,0,1000,1000,16777216,0};

    PixelDataElement p1 = {0,0,0};
    PixelDataElement p2 = {0,0,1};
    PixelDataElement p3 = {0,1,0};

    PixelDataElement p4 = {0,1,1};
    PixelDataElement p5 = {1,0,0};
    PixelDataElement p6 = {1,0,1};

    PixelDataElement p7 = {1,1,0};
    PixelDataElement p8 = {1,1,1};
    PixelDataElement p9 = {0,0,0};

    PixelDataElement pTab[9] = {p1,p2,p3,p4,p5,p6,p7,p8,p9};

    BitMap theBMP = {theHeader,theInfoHeader,pTab};
    FILE * fileBMP = fopen("test.bmp","wb");
    fwrite(&theBMP,theBMP.infoHeader.Size,1,fileBMP);
    fclose(fileBMP);
    return 0;
}
