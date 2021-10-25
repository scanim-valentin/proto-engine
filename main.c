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
    M = Physics_snapshot();
    BMP_256_printMatrix(M.Matrix,M.Dimensions.x,M.Dimensions.y,"it0.bmp");
    return 0;
}
