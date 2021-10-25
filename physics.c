#include "physics.h"
#include "pixel_matrices.h"
#include <stdio.h>
#define NB_MAX_SQUARES 10
#define NB_MAX_RECTANGLES 10
#define NB_MAX_CIRCLES 10

Square Square_tab[NB_MAX_SQUARES];
int square_last_index = 0;

Rectangle Rectangle_tab[NB_MAX_RECTANGLES];
int rectangle_last_index = 0;

Circle Circle_tab[NB_MAX_CIRCLES];
int circle_last_index = 0;


void Physics_AddSquare(int x,int y,int s){
    Square S = {x,y,s};
    Square_tab[square_last_index] = S;
    square_last_index++;
    printf("Added 1 square (x %d y %d s %d)\n",x,y,s);
}

void Physics_AddRectangle(int x,int y,int s1, int s2){
    Rectangle S = {x,y,s1,s2};
    Rectangle_tab[rectangle_last_index] = S;
    rectangle_last_index++;
    printf("Added 1 rectangle (x %d y %d sx %d sy %d)\n",x,y,s1,s2);
}

void Physics_AddCircle(int x,int y,int r){
    Circle S = {x,y,r};
    Circle_tab[circle_last_index] = S;
    circle_last_index++;
    printf("Added 1 circle (x %d y %d r %d)\n",x,y,r);
}

MatrixData Physics_snapshot(){
    int resX = 1000 ;
    int resY = 1000 ;

    PixelDataElement map(PixelParameters * p){
        PixelDataElement R = {0,0,0};
        int i = p->Coordinates->i ;
        int j = p->Coordinates->j ;
        for(int k = 0 ; k<square_last_index ; k++){
            char is_in_square = (i >= Square_tab[k].y) && (i <= ( Square_tab[k].y + Square_tab[k].s ) ) && (j >= Square_tab[k].x) && (j <= ( Square_tab[k].x + Square_tab[k].s ) );
            if(is_in_square){
                R.Red = 255 ;
                R.Green = 0 ;
                R.Blue = 0 ;

            }
        }
        for(int k = 0 ; k<rectangle_last_index ; k++){
            char is_in_rectangle = (i >= Rectangle_tab[k].y) && (i <= ( Rectangle_tab[k].y + Rectangle_tab[k].sy ) ) && (j >= Rectangle_tab[k].x) && (j <= ( Rectangle_tab[k].x + Rectangle_tab[k].sx ) );
            if(is_in_rectangle){
                R.Red = 0 ;
                R.Green = 255 ;
                R.Blue = 0 ;

            }
        }
        for(int k = 0 ; k<square_last_index ; k++){
            int y = Circle_tab[k].y;
            int x = Circle_tab[k].x;
            int r_c = Circle_tab[k].r*Circle_tab[k].r;
            char is_in_circle = ( (x-j)*(x-j) + (y-i)*(y-i) <= r_c );
            if(is_in_circle){
                R.Red = 0 ;
                R.Green = 0 ;
                R.Blue = 255 ;
            }
        }

        return R ;
    }
    return Pixel256Matrix(map,resX,resY);
}
