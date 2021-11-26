#include <stdio.h>
#include <stdlib.h>
#include "bmp_management.h"

void BMP_256_printMatrix(PixelDataElement * matrix[], int resX, int resY, char * fileName ){
    printf("Calling : %s . . . \n", __func__);
    //Creating the header

    int zero_padding; //Each scan line is zero padded to the nearest 4-byte boundary

    if(4 == (zero_padding = 4 - ( (resX*3) % 4 )))
        zero_padding = 0 ;

    printf("- Size of zero padding / scan line  : %d bytes \n", zero_padding);
    int offset = sizeof(Header)+sizeof(InfoHeader);
    int sizeOfMatrix = resX*resY*3;
    Header H = {0x4D42,sizeOfMatrix+zero_padding+offset,0,offset};
    InfoHeader IH = {sizeof(InfoHeader),//size of infoheader
        resX,//width
        resY,//height
        1,//planes
        24,//bits per pixel
        0,//compression
        sizeOfMatrix * 3,//(compressed) size of the image (supposedly valid to set to 0 if no compression)
        10,//horizontal resolution
        10, //vertical resolution
        16777216,//Number of colors
        0}; //Important colors (0 = all)
        
    //Writing Header and InfoHeader into the file
    FILE * fileBMP = fopen(fileName,"wb");
    printf("- Created %s \n", fileName);

    fwrite(&H,sizeof(Header),1,fileBMP);
    fwrite(&IH,sizeof(InfoHeader),1,fileBMP);
    
    //Writing the matrix and the zero padding into the file
    char zero = 0 ; 
    printf("- Writing into the file . . . \n");

    for(int i = 0 ; i < resY ; i++ ){
        for(int j = 0 ; j < resX ; j++ ){
            //printf(" R%dG%dB%d ", matrix[i][j].Red, matrix[i][j].Green, matrix[i][j].Blue);
            fwrite(&(matrix[i][j]),sizeof(char)*3,1,fileBMP);
        }
        
        for( int k = 0 ; k < zero_padding ; k++ ){
            //printf(" 0 ");
            fwrite(&(zero),sizeof(char),1,fileBMP);
        }
        //printf(" \n ");

    }
    fclose(fileBMP);
    printf("- Done. \n");
}
