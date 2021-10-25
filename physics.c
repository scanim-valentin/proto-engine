#include "physics.h"
#include "pixel_matrices.h"
#include <stdio.h>
#define NB_MAX_SQUARES 10

Square Square_tab[NB_MAX_SQUARES];
int square_last_index = 0;

void Physics_AddSquare(int x,int y,int s){
    Square S = {x,y,s};
    Square_tab[square_last_index] = S;
    square_last_index++;
    printf("Added 1 square (%d %d %d)\n",x,y,s);
}

MatrixData Physics_snapshot(){
    int resX = 1000 ;
    int resY = 1000 ;
    PixelDataElement map(PixelParameters * p){
        int i = p->Coordinates->i ;
        int j = p->Coordinates->j ;
        for(int k = 0 ; k<square_last_index ; k++){
            char is_in_square = (i >= Square_tab[k].y) && (i <= ( Square_tab[k].y + Square_tab[k].s ) ) && (j >= Square_tab[k].x) && (j <= ( Square_tab[k].x + Square_tab[k].s ) );
            if(is_in_square){
                PixelDataElement R = {0,0,255};
                return R;
            }else{
                PixelDataElement R = {0,0,0};
                return R;
            }
        }
    }
    return Pixel256Matrix(map,resX,resY);
}
