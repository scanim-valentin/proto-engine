#include "bmp_management.h"
#include <stdio.h>

void BMP_256_printMatrix(PixelDataElement * matrix[], int resX, int resY, char * fileName ){
    
    //Creating the header
    int zero_padding = resX % 4; //Each scan line is zero padded to the nearest 4-byte boundary
    int offset = sizeof(Header);
    int sizeOfMatrix = resX*resY; 
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
    fwrite(&H,sizeof(Header),1,fileBMP);
    fwrite(&IH,sizeof(InfoHeader),1,fileBMP);
    
    //Writing the matrix and the zero padding into the file
    char zero = 0 ; 
    for(int i = 0 ; i < resY ; i++ ){
        for(int j = 0 ; j < resX ; j++ ){
            fwrite(&(matrix[i][j]),sizeof(char),1,fileBMP);
        }
        
        for( int k = 0 ; k < zero_padding ; k++ ){            
            fwrite(&(zero),sizeof(char),1,fileBMP);
        }
    }
    fclose(fileBMP);
}
