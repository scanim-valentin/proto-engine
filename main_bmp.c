#include "bmp_management.h"
#include <stdio.h>

#define NB_PIXELS 9
int main(){

    Header theHeader = {0x4D42,(unsigned long)(54+3*NB_PIXELS),0,54};

    printf("Taille du fichier = %d\n",theHeader.FileSize);
    InfoHeader theInfoHeader = {40,3,3,1,24,0,0,1000,1000,16777216,0};

    PixelDataElement p1 = {0,0,0};
    PixelDataElement p2 = {0,0,254};
    PixelDataElement p3 = {0,254,0};

    PixelDataElement p4 = {0,254,254};
    PixelDataElement p5 = {254,0,0};
    PixelDataElement p6 = {254,0,254};

    PixelDataElement p7 = {254,254,0};
    PixelDataElement p8 = {254,254,254};
    PixelDataElement p9 = {0,0,0};

    PixelDataElement pTab[9] = {p1,p2,p3,p4,p5,p6,p7,p8,p9};

    BitMap theBMP = {theHeader,theInfoHeader,pTab};
    FILE * fileBMP = fopen("test.bmp","wb");
    fwrite(&theBMP,81,1,fileBMP);
    fclose(fileBMP);
    return 0;
}
