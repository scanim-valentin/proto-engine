
#include <stdio.h>
#include <stdlib.h>
#include "../include/pixel_matrices.h"

MatrixData Pixel256MatrixOP(PixelDataElement map(PixelParameters *, MatrixData), MatrixData data, MatrixDimensions result_dim){
    PixelCoordinates pos;
    PixelParameters param = {&pos,&result_dim};
    PixelDataElement * * matrix = malloc(sizeof(PixelDataElement *)*result_dim.y);

    for(pos.i = 0 ; pos.i < result_dim.y ; (pos.i)++){
        PixelDataElement * line = malloc(sizeof(PixelDataElement)*result_dim.x);
        for(pos.j = 0 ; pos.j < result_dim.x ; (pos.j)++){

            line[pos.j] = map(&param, data);
        }
        matrix[pos.i] = line;
    }
    MatrixData mat_data = {matrix, result_dim};
    return mat_data;
}

MatrixData Pixel256Matrix(PixelDataElement map(PixelParameters *), int resX, int resY){

    PixelDataElement map2(PixelParameters * param, MatrixData data){
        return map(param);
    }

    MatrixDimensions dim = {resX,resY};
    MatrixData zero;
    MatrixData R = Pixel256MatrixOP(map2,zero,dim);
    return R;

}


//Defining some basic operations on RGB matrices

MatrixData Pixel256MatrixTranspose(MatrixData data){

    PixelDataElement map(PixelParameters * param, MatrixData data){
        int new_j = data.Dimensions.x - 1 - param->Coordinates->i;
        int new_i = data.Dimensions.y - 1 - param->Coordinates->j;
        PixelDataElement R = {data.Matrix[new_i][new_j].Blue,data.Matrix[new_i][new_j].Green,data.Matrix[new_i][new_j].Red};
        return R;
    }

    MatrixDimensions dim = {data.Dimensions.y,data.Dimensions.x};
    MatrixData R = Pixel256MatrixOP(map,data,dim);
    return R;

}

MatrixData Pixel256MatrixVerticalMirror(MatrixData data){

    PixelDataElement map(PixelParameters * param, MatrixData data){
        int new_i = param->Coordinates->i;
        int new_j = data.Dimensions.x - 1 - param->Coordinates->j;
        PixelDataElement R = {data.Matrix[new_i][new_j].Blue,data.Matrix[new_i][new_j].Green,data.Matrix[new_i][new_j].Red};
        return R;
    }

    MatrixData R = Pixel256MatrixOP(map,data,data.Dimensions);
    return R;

}

MatrixData Pixel256MatrixHorizontalMirror(MatrixData data){

    PixelDataElement map(PixelParameters * param, MatrixData data){
        int new_i = data.Dimensions.y - 1 - param->Coordinates->i;
        int new_j = param->Coordinates->j;
        PixelDataElement R = {data.Matrix[new_i][new_j].Blue,data.Matrix[new_i][new_j].Green,data.Matrix[new_i][new_j].Red};
        return R;
    }

    MatrixData R = Pixel256MatrixOP(map,data,data.Dimensions);
    return R;

}

/*
*à revoir
*/

//Some operations on RGB vectors

//A structure dedicated to the sole purpose of allowing more room to do operations on RGB vectors
typedef struct double_rgb{
    double Blue;
    double Green;
    double Red;
} DoublePixel;

DoublePixel RGBCharToDoublePixel(PixelDataElement A){
    DoublePixel R = {(double)(A.Blue) , (double)(A.Green), (double)(A.Red)};
    return R;
}

PixelDataElement RGBDoubleToCharPixel(DoublePixel A){
    PixelDataElement R = {(char)(A.Blue) , (char)(A.Green), (char)(A.Red)};
    return R;
}


DoublePixel RGBDoubleSum(DoublePixel A, DoublePixel B){
    DoublePixel R = {(double)(A.Blue)+(double)(B.Blue) , (double)(A.Green)+(double)(B.Green), (double)(A.Red)+(double)(B.Red)};
    return R;
}

DoublePixel RGBDivideByScalar(DoublePixel A, double x){
    DoublePixel R = {A.Blue/x , A.Green/x, A.Red/x};
    return R;
}

// ! Make sure size is big enough to allow proper casting to char
PixelDataElement RGBAverageValue(PixelDataElement * * PixelTab, int size){
    DoublePixel S = {0,0,0};
    for(int i = 0 ; i < size ; i++){
        S = RGBDoubleSum( S , RGBCharToDoublePixel( *PixelTab[i] ) );
    }
    S = RGBDivideByScalar(S, size);
    PixelDataElement R = RGBDoubleToCharPixel(S);
    return R;
}

MatrixData Pixel256MatrixBlur(MatrixData data){
    PixelDataElement map(PixelParameters * param, MatrixData data){
        int i = param->Coordinates->i;
        int j = param->Coordinates->j;
        int dimX = data.Dimensions.x;
        int dimY = data.Dimensions.y;
        PixelDataElement * * M = data.Matrix ;

        char left_side = ( j == 0 ) && ( i != 0 ) && ( i != ( dimY - 1 ) ) ;
        char right_side = ( j == ( dimX - 1 ) ) && ( i != 0 ) && ( i != ( dimY - 1 ) ) ;
        char upper_side = ( i == ( dimY - 1 ) ) && ( j != 0 ) && ( j != ( dimX - 1 ) ) ;
        char bottom_side = ( i == 0 ) && ( j != 0 ) && ( j != ( dimX - 1 ) ) ;
        char bottom_left_corner = ( i == 0 ) && ( j == 0 );
        char bottom_right_corner = ( i == 0 ) && ( j == ( dimX - 1 ) );
        char upper_right_corner = ( i == ( dimY - 1 ) ) && ( j == ( dimX - 1 ) );
        char upper_left_corner = ( i == ( dimY - 1 ) ) && ( j == 0 );

        double nb_neighbors;
        if( left_side ){
            nb_neighbors = 6 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i+1][j]) , &(M[i+1][j+1]), &(M[i][j+1]), &(M[i-1][j+1]), &(M[i-1][j])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( right_side ){
            nb_neighbors = 6 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i+1][j]) , &(M[i+1][j-1]), &(M[i][j-1]), &(M[i-1][j-1]), &(M[i-1][j])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( upper_side ){
            nb_neighbors = 6 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i][j-1]) , &(M[i-1][j-1]), &(M[i-1][j]), &(M[i-1][j+1]), &(M[i][j+1])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( bottom_side ){
            nb_neighbors = 6 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i][j-1]) , &(M[i+1][j-1]), &(M[i+1][j]), &(M[i+1][j+1]), &(M[i][j+1])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( bottom_left_corner ){
            nb_neighbors = 4 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i+1][j]) , &(M[i+1][j+1]), &(M[i][j+1])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( bottom_right_corner ){
            nb_neighbors = 4 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i+1][j]) , &(M[i+1][j-1]), &(M[i][j-1])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( upper_right_corner ){
            nb_neighbors = 4 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i][j-1]) , &(M[i-1][j-1]), &(M[i-1][j])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else if( upper_left_corner ){
            nb_neighbors = 4 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i-1][j]), &(M[i-1][j+1]), &(M[i][j+1])};
            return RGBAverageValue(neighbors,nb_neighbors);

        } else{
            nb_neighbors = 9 ;
            PixelDataElement * neighbors[] = {&(M[i][j]), &(M[i+1][j]) , &(M[i+1][j+1]), &(M[i][j+1]), &(M[i-1][j+1]), &(M[i-1][j]),&(M[i+1][j-1]), &(M[i][j-1]), &(M[i-1][j-1])};
             return RGBAverageValue(neighbors,nb_neighbors);

        }
        PixelDataElement dummypix = {203,192,255};
        return dummypix;

    }

    MatrixData R = Pixel256MatrixOP(map,data,data.Dimensions);
    return R;
}
