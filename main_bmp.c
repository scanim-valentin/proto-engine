#include "bmp_management.h"
#include <stdio.h>

int main(){

    //printf("%d",BMP_256_testMatrixAllBlack(BMP_256_allBlack(1000,1000), 1000, 1000));
    BMP_256_printMatrix(BMP_256_testProgressive(1000,1000),1000,1000,"progressive2.bmp");
    
    return 0;
}
