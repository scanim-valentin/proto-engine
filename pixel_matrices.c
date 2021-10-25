
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
