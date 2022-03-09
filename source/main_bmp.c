#include "../include/bmp_management.h"
#include "../include/pixel_matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

PixelDataElement map_Progressive(PixelParameters * param){
    unsigned char n = (param->Coordinates->i)*(param->Dimensions->x)+(param->Coordinates->j)*3;
    PixelDataElement  R = {n,n+1,n+2};
    return R;
}

PixelDataElement map_MathAreFun(PixelParameters * param){
    int i = param->Coordinates->i;
    int j = param->Coordinates->j;
    int resX = param->Dimensions->x;
    int resY = param->Dimensions->y;
    double phi = 2.0*3.14*(double)j/(((double)resX/4.0)+1.0) ;
    double testValue = ( (resY/2)+sin(phi)*(resY/4) ) ;
    double testValue2 = ( (resY/2)+cos(phi)*(resY/4) ) ;
    if( ( i == (int)testValue ) || ( i == (int)testValue2 ) || ( i == (int)(200*exp((1.0)/((double)j/20.)) ) ) | (i == (int)(50*log(j))) ){
        PixelDataElement R = {255,255,255};
        return R;
    }
    else{
        PixelDataElement R = {0,0,0};
        return R;
    }
}

PixelDataElement map_black(PixelParameters * param){
    PixelDataElement R = {0,0,0};
    return R;
}

PixelDataElement map_Mystery(PixelParameters * param){
    PixelDataElement R = {param->Coordinates->j,param->Coordinates->i,param->Coordinates->i+param->Coordinates->j};
    return R;
}

PixelDataElement map_Mystery2(PixelParameters * param){
    int i = param->Coordinates->i;
    int j = param->Coordinates->j;
    PixelDataElement R = {i/(j+1),j/(i+1),i+j/(j*i+1)};
    return R;
}

int main(){
    MatrixData M;

    M = Pixel256Matrix(map_Mystery2,255,255);
//     char str[80];
    BMP_256_printMatrix(M.Matrix,M.Dimensions.x,M.Dimensions.y,"mystery.bmp");
//     for(int i = 1 ; i < 10 ; i++){
//         M = Pixel256MatrixBlur(M);
//         sprintf(str,"it%d.bmp",i);
//         BMP_256_printMatrix(M.Matrix,M.Dimensions.x,M.Dimensions.y,str);
//     }
    return 0;
}
