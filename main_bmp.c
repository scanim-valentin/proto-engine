#include "bmp_management.h"

int main(){

    BMP_256_printMatrix(BMP_256_testProgressive(3,3),3,3,"new_test.bmp");
    
    return 0;
}
