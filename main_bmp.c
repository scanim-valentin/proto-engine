#include "bmp_management.h"
#include <stdio.h>

#define NB_PIXELS 9
int main(){

    Header theHeader = {0x4D42,(unsigned long)(54+3*NB_PIXELS),0,45};

    printf("Taille du fichier = %d\n",theHeader.FileSize);
    InfoHeader theInfoHeader = {40,//size of infoheader
        3,//width
        3,//height
        1,//planes
        24,//bits per pixel
        0,//compression
        9*3,//(compressed) size of the image (supposedly valid to set to 0 if no compression)
        10,//horizontal resolution
        10, //vertical resolution
        16777216,//Number of colors
        0}; //Important colors (0 = all)

    PixelDataElement p1 = {0,1,2};
    PixelDataElement p2 = {3,4,5};
    PixelDataElement p3 = {6,7,8};

    PixelDataElement p4 = {9,10,11};
    PixelDataElement p5 = {12,13,14};
    PixelDataElement p6 = {15,16,17};

    PixelDataElement p7 = {18,19,20};
    PixelDataElement p8 = {21,22,23};
    PixelDataElement p9 = {24,25,26};
    
    PixelDataElement zero_pad = {0,0,0};
    
    PixelDataElement pTab[12] = {p1,p2,p3,zero_pad,p4,p5,p6,zero_pad,p7,p8,p9,zero_pad};
    //Each scan line is zero padded to the nearest 4-byte boundary. If the image has a width that is not divisible by four, say, 21 bytes, there would be 3 bytes of padding at the end of every scan line.
    //BitMap theBMP = {theHeader,theInfoHeader,pTab};
    FILE * fileBMP = fopen("test.bmp","wb");
    //fwrite(&theBMP,91,1,fileBMP);
    fwrite(&theHeader,sizeof(Header),1,fileBMP);
    fwrite(&theInfoHeader,sizeof(InfoHeader),1,fileBMP);
    for(int i = 0 ; i < 12 ; i++){
        printf("i = %d : %p | R %d G %d B %d \n",i,&(pTab[i]),pTab[i].Red,pTab[i].Green,pTab[i].Blue);
        fwrite(&(pTab[i]),sizeof(char)*3,1,fileBMP);
    }
    fclose(fileBMP);
    return 0;
}
