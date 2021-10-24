#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp_management.h"
PixelDataElement * BMP_256_createPixel(unsigned char Red, unsigned char Green, unsigned char Blue){
    PixelDataElement  * R = malloc(sizeof(PixelDataElement));
    R->Red = Red;
    R->Green = Green;
    R->Blue = Blue;
    return R;
}
//Test function : matrix test all black
int BMP_256_testMatrixAllBlack(PixelDataElement * * matrix, int resX, int resY){
    printf("Calling : %s . . . \n", __func__);
      for(int i = 0 ; i < resY ; i++ ){
        for(int j = 0 ; j < resX ; j++ ){
            if((matrix[i][j].Red != 0) || (matrix[i][j].Green != 0) || (matrix[i][j].Blue != 0)){
                //printf(" R%dG%dB%d ", line[j].Red, line[j].Green, line[j].Blue);
                printf("- Failure! M[%d][%d] = R%d G%d B%d\n",i,j,matrix[i][j].Red, matrix[i][j].Green, matrix[i][j].Blue);
                exit(1);
            }
        }
    }
    return 0;
}
//Test function : generate a resY x resY pixel matrix of progressively bright pixel (bitmap data should follow n=n+1 pattern)
PixelDataElement * * BMP_256_testProgressive(int resX, int resY){
    printf(" Progressive Matrix Creation \n ");
    PixelDataElement * * matrix = malloc(sizeof(PixelDataElement*)*resY);
    for(int i = 0 ; i < resY ; i++ ){
        PixelDataElement * line = malloc(sizeof(PixelDataElement)*resX);;
        for(int j = 0 ; j < resX ; j++ ){
            unsigned char n = i*resX+j*3;
            line[j] = *BMP_256_createPixel(n,n+1,n+2) ;
            printf(" R%dG%dB%d ", line[j].Red, line[j].Green, line[j].Blue);
        }
        matrix[i] = line;
        printf("\n");
    }
    return matrix;
}

//Test function : generate a resY x resY pixel matrix of progressively bright pixel (bitmap data should follow n=n+1 pattern)
PixelDataElement * * BMP_256_allBlack(int resX, int resY){
   printf("Calling : %s . . . \n", __func__);
    PixelDataElement * * matrix = malloc(sizeof(PixelDataElement *)*resY);
    for(int i = 0 ; i < resY ; i++ ){
        PixelDataElement * line = malloc(sizeof(PixelDataElement)*resX);;
        for(int j = 0 ; j < resX ; j++ ){
            line[j] = *BMP_256_createPixel(0,0,0) ;
            //printf(" R%dG%dB%d ", line[j].Red, line[j].Green, line[j].Blue);
            if((line[j].Red != 0) || (line[j].Green != 0) || (line[j].Blue != 0)){
                printf("- Failure! 1");
                exit(1);
            }
        }
        matrix[i] = line;
        //printf("\n");
    }

    for(int i = 0 ; i < resY ; i++ ){
        for(int j = 0 ; j < resX ; j++ ){
            if((matrix[i][j].Red != 0) || (matrix[i][j].Green != 0) || (matrix[i][j].Blue != 0)){
                //printf(" R%dG%dB%d ", line[j].Red, line[j].Green, line[j].Blue);
                printf("- Failure! M[%d][%d] = R%d G%d B%d\n",i,j,matrix[i][j].Red, matrix[i][j].Green, matrix[i][j].Blue);
                exit(1);
            }
        }
    }
    return matrix;
}

//Test function : generate a resY x resY pixel matrix of progressively bright pixel (bitmap data should follow n=n+1 pattern)
PixelDataElement * * BMP_256_testMystery(int resX, int resY){
    printf(" Progressive Matrix Creation \n ");
    PixelDataElement * * matrix = malloc(sizeof(PixelDataElement *)*resY);
    for(int i = 0 ; i < resY ; i++ ){
        PixelDataElement * line = malloc(sizeof(PixelDataElement)*resX);;
        for(int j = 0 ; j < resX ; j++ )
            line[j] = *BMP_256_createPixel(i,j,i+j) ;
        matrix[i] = line;
    }
    return matrix;
}

PixelDataElement * * BMP_256_testMystery2(int resX, int resY){
    printf("Calling : %s . . . \n", __func__);
    PixelDataElement * * matrix = malloc(sizeof(PixelDataElement*)*resY);
    for(int i = 0 ; i < resY ; i++ ){
        PixelDataElement * line = malloc(sizeof(PixelDataElement)*resX);;
        for(int j = 0 ; j < resX ; j++ ){
            line[j] = *BMP_256_createPixel(i/(j+1),j/(i+1),i+j/(j*i+1)) ;
            //printf(" R%dG%dB%d ", line[j].Red, line[j].Green, line[j].Blue);
        }
        matrix[i] = line;
        //printf("\n");
    }
    return matrix;
}

PixelDataElement * * BMP_256_testSinus(int resX, int resY){
    printf(" Progressive Matrix Creation \n ");
    PixelDataElement * * matrix = malloc(sizeof(PixelDataElement*)*resY);
    for(int i = 0 ; i < resY ; i++ ){
        PixelDataElement * line = malloc(sizeof(PixelDataElement)*resX);;
        for(int j = 0 ; j < resX ; j++ ){
            double phi = 2.0*3.14*(double)j/(((double)resX/4.0)+1.0) ;
            double testValue = ( (resY/2)+sin(phi)*(resY/4) ) ;
            double testValue2 = ( (resY/2)+cos(phi)*(resY/4) ) ;
            printf("%d ",(int)(200*exp((1.0)/(double)j)) );
            if( ( i == (int)testValue ) || ( i == (int)testValue2 ) || ( i == (int)(200*exp((1.0)/((double)j/20.)) ) ) | (i == (int)(50*log(j))) )
                line[j] = *BMP_256_createPixel(255,255,255) ;
            else
                line[j] = *BMP_256_createPixel(0,0,0) ;
            //printf(" R%dG%dB%d ", line[j].Red, line[j].Green, line[j].Blue);
        }
        matrix[i] = line;
        //printf("\n");
    }
    return matrix;
}


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
