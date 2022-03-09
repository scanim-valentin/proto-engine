#ifndef STATICS
#define STATICS
#include "../include/pixel_matrices.h"
#define NB_MAX_SHAPES 100


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

typedef struct ellipse{

	int x; //Coordinates of the center
	int y;
	int rx;
    int ry;

}	Ellipse;

typedef union shape{
    Square * S ;
    Circle * C ;
    Ellipse * E ;
    Rectangle * R ;

} Shape ;

typedef struct scene{

    Shape * ShapeArray ;
    int sizeOfShapeArray ;

}	Scene;

typedef struct cell{
    Shape sh ;
    struct cell * next ;
} Cell ;

Scene * Physics_initScene();

void Physics_AddCircle(Scene * S, int x,int y,int r) ;
void Physics_AddEllipse(Scene * S, int x,int y,int rx, int ry) ;
void Physics_AddRectangle(Scene * S, int x,int y,int s1, int s2) ;
void Physics_AddSquare(Scene * S, int x,int y,int s) ;

MatrixData Physics_snapshot();

#endif
