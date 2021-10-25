#include "bmp_management.h"
#include "pixel_matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

PixelDataElement map_Progressive(PixelParameters * param){
    unsigned char n = (param->Coordinates->i)*(param->Dimensions->x)+(param->Coordinates->j)*3;
    PixelDataElement  R = {n,n+1,n+2};
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


int main(){

    //printf("%d",BMP_256_testMatrixAllBlack(BMP_256_allBlack(1000,1000), 1000, 1000));
    MatrixData M;

    M = Pixel256Matrix(map_Progressive,1500,1200);

    BMP_256_printMatrix(M.Matrix,M.Dimensions.x,M.Dimensions.y,"test.bmp");
    
    return 0;
}
