#include "bmp_management.h"
#include "pixel_matrices.h"
#include "physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    MatrixData M;
    Physics_AddSquare(250,250,250);
    Physics_AddCircle(500,200,100);
    Physics_AddRectangle(900,100,100,200);
    M = Physics_snapshot();
    M = Pixel256MatrixBlur(M);
    BMP_256_printMatrix(M.Matrix,M.Dimensions.x,M.Dimensions.y,"it0.bmp");
    return 0;
}
