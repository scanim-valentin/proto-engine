#include <stdint.h>

typedef struct __attribute__((__packed__)) header{ //__attribute__((__packed__)) will make sure GCC packs the structure
    unsigned short Signature; //'BM'
    uint32_t FileSize; //File size in bytes
    uint32_t reserved; //unused (=0)
    uint32_t DataOffset; //Offset from beginning of file to the beginning of the bitmap data
} Header;

typedef struct __attribute__((__packed__)) infoheader{
    uint32_t Size; //Size of InfoHeader =40
    uint32_t Width; //Horizontal width of bitmap in pixels
    uint32_t Height; //Vertical height of bitmap in pixels
    unsigned short Planes; //Number of Planes (=1)
    unsigned short BitsPerPixel; /* Bits per Pixel used to store palette entry information. This also identifies in an indirect way the number of possible colors. Possible values are:
    1 = monochrome palette. NumColors = 1
    4 = 4bit palletized. NumColors = 16
    8 = 8bit palletized. NumColors = 256
    16 = 16bit RGB. NumColors = 65536
    24 = 24bit RGB. NumColors = 16M */
    uint32_t Compression; /*Type of Compression
    0 = BI_RGB   no compression
    1 = BI_RLE8 8bit RLE encoding
    2 = BI_RLE4 4bit RLE encoding*/
    uint32_t ImageSize; //(compressed) Size of Image, it is valid to set this =0 if Compression = 0
    uint32_t XpixelsPerM; //horizontal resolution: Pixels/meter
    uint32_t YpixelsPerM; //vertical resolution: Pixels/meter
    uint32_t ColorUsed; //Number of actually used colors. For a 8-bit / pixel bitmap this will be 100h or 256.
    uint32_t ImportantColors; //Number of important colors, 0 = all


} InfoHeader;

typedef struct __attribute__((__packed__)) colortableelement{ //Element of palette - unusued if InfoHeader.BitsPerPixel >= 16
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
    unsigned char reserved; //unused
} ColorTableElement;

typedef struct __attribute__((__packed__)) pixeldataelement{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
} PixelDataElement;

typedef struct __attribute__((__packed__)) bitmap_palette{
    Header header;
    InfoHeader infoHeader;
    ColorTableElement * colorTable;
    PixelDataElement * pixelData;
} BitMap_Palette;

typedef struct __attribute__((__packed__)) bitmap{
    Header header;
    InfoHeader infoHeader;
    PixelDataElement * pixelData;
} BitMap;

int BMP_256_convertToMatrix(char * path);
void BMP_256_printMatrix(PixelDataElement * matrix[], int resX, int resY, char * FileName );

//For testing
PixelDataElement * * BMP_256_testProgressive(int resX, int resY);
PixelDataElement * * BMP_256_testMystery(int resX, int resY);
PixelDataElement * * BMP_256_testMystery2(int resX, int resY);

PixelDataElement * * BMP_256_testSinus(int resX, int resY);
PixelDataElement * * BMP_256_allBlack(int resX, int resY);
int BMP_256_testMatrixAllBlack(PixelDataElement * * M, int resX, int resY) ;
