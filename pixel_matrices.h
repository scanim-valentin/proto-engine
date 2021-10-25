#ifndef PIXEL_MATRICES
#define PIXEL_MATRICES

typedef struct __attribute__((__packed__)) pixeldataelement{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
} PixelDataElement;


typedef struct matrixdim{
    unsigned int x;
    unsigned int y;
} MatrixDimensions;

typedef struct coordinates{
    unsigned int i;
    unsigned int j;
} PixelCoordinates;

typedef struct pixel_params{
    PixelCoordinates * Coordinates;
    MatrixDimensions * Dimensions;
} PixelParameters;

typedef struct matrix_data{
    PixelDataElement * * Matrix;
    MatrixDimensions Dimensions;
} MatrixData;


//Matrix generation

//This functions allows to define each pixel based on its coordinates and the dimensions of the matrix. (See PixelParameters struct above)
MatrixData Pixel256Matrix(PixelDataElement map(PixelParameters *), int resX, int resY);

//Defining some basic operations on RGB matrices

//This functions allows to define each pixel based on its coordinates and the data (pixels+dim) of another matrix.
MatrixData Pixel256MatrixOP(PixelDataElement map(PixelParameters *, MatrixData data), MatrixData data, MatrixDimensions result_dim);

//Returns the transposed version of a matrix
MatrixData Pixel256MatrixTranspose(MatrixData data);

//Returns the mirrored version of a matrix
MatrixData Pixel256MatrixVerticalMirror(MatrixData data);
MatrixData Pixel256MatrixHorizontalMirror(MatrixData data);

#endif
