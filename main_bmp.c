#include "bmp_management.h"
#include <stdio.h>

#define NB_PIXELS 9
int main(){

    Header theHeader = {0x4D42,(unsigned long)(54+3*NB_PIXELS),0,45};

    printf("Taille du fichier = %d\n",theHeader.FileSize);
    InfoHeader theInfoHeader = {40,3,3,1,24,0,0,10,10,16777216,0};

    PixelDataElement p1 = {0,1,2};
    PixelDataElement p2 = {3,4,5};
    PixelDataElement p3 = {6,7,8};

    PixelDataElement p4 = {9,10,11};
    PixelDataElement p5 = {12,13,14};
    PixelDataElement p6 = {15,16,17};

    PixelDataElement p7 = {18,19,20};
    PixelDataElement p8 = {21,22,23};
    PixelDataElement p9 = {24,25,27};

    PixelDataElement pTab[9] = {p1,p2,p3,p4,p5,p6,p7,p8,p9};

    //BitMap theBMP = {theHeader,theInfoHeader,pTab};
    FILE * fileBMP = fopen("test.bmp","wb");
    //fwrite(&theBMP,91,1,fileBMP);
    fwrite(&theHeader,sizeof(Header),1,fileBMP);
    fwrite(&theInfoHeader,sizeof(InfoHeader),1,fileBMP);
    for(int i = 0 ; i < 10 ; i++){
        printf("i = %d : %p | R %d G %d B %d \n",i,&(pTab[i]),pTab[i].Red,pTab[i].Blue,pTab[i].Green);
        fwrite(&(pTab[i]),sizeof(PixelDataElement),1,fileBMP);
    }
    fclose(fileBMP);
    return 0;
}
