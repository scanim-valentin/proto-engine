#include "../include/physics.h"
#include "../include/pixel_matrices.h"
#include <stdio.h>
#include <stdlib.h>

Scene * Physics_initScene(){

    Scene * S = malloc(sizeof(Scene)) ;
    return S ;
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
        for(int k = 0 ; k<circle_last_index ; k++){
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

        for(int k = 0 ; k<ellipse_last_index ; k++){
            float y = (float)Ellipse_tab[k].y;
            float x = (float)Ellipse_tab[k].x;
            float rx_c = (float)Ellipse_tab[k].rx*(float)Ellipse_tab[k].rx;
            float ry_c = (float)Ellipse_tab[k].ry*(float)Ellipse_tab[k].ry;
            char is_in_ellipse = ( (x-j)*(x-j)/rx_c + (y-i)*(y-i)/ry_c <= 1.0 );
            if(is_in_ellipse){
                R.Red = 255 ;
                R.Green = 0 ;
                R.Blue = 255 ;
            }
        }

        return R ;
    }
    return Pixel256Matrix(map,resX,resY);
}
