
#include <stdio.h>
#include <stdlib.h>
#include "pixel_matrices.h"

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

PixelDataElement RGBSum(PixelDataElement A, PixelDataElement B){
    PixelDataElement R = {A.Blue+B.Blue , A.Green+B.Green, A.Red+B.Red};
    return R;
}

PixelDataElement RGBDivideByScalar(PixelDataElement A, char x){
    PixelDataElement R = {A.Blue/x , A.Green/x, A.Red/x};
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
MatrixData Pixel256MatrixBlur(MatrixData data){
    PixelDataElement map(PixelParameters * param, MatrixData data){
        int i = param->Coordinates->i;
        int j = param->Coordinates->j;
        PixelDataElement R = {0,0,0};

        if(j == data.Dimensions.x-1)
            R = RGBSum(R,data.Matrix[i][j-1]);
        else if(j == 0)
            R = RGBSum(R,data.Matrix[i][j+1]);
        else
            R = RGBSum(RGBSum(R,data.Matrix[i][j-1]),data.Matrix[i][j+1]);

        if(i == data.Dimensions.y-1)
            R = RGBSum(R,data.Matrix[i-1][j]);
        else if(i == 0)
            R = RGBSum(R,data.Matrix[i+1][j]);
        else
            R = RGBSum(RGBSum(R,data.Matrix[i-1][j]),data.Matrix[i+1][j]);

        return RGBDivideByScalar(R,4);
    }

    MatrixData R = Pixel256MatrixOP(map,data,data.Dimensions);
    return R;
}
