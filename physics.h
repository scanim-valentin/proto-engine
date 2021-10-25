#ifndef STATICS
#define STATICS
#include "pixel_matrices.h"

typedef struct square{

	int x; //Coordinates of the bottom left corner
	int y;
	int s; //Size of the sides

}	Square;

typedef struct rectangle{

	int x; //Coordinates of the bottom left corner
	int y;
	int sx;
    int sy;

}	Rectangle;

typedef struct circle{

	int x; //Coordinates of the center
	int y;
	int r; //Radius

}	Circle;

void Physics_AddCircle(int x,int y,int r) ;
void Physics_AddRectangle(int x,int y,int s1, int s2) ;
void Physics_AddSquare(int x,int y,int s) ;

MatrixData Physics_snapshot();

#endif
