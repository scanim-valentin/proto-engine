typedef struct header{
	unsigned short Signature; //'BM'
	unsigned long FileSize; //File size in bytes
	unsigned long reserved; //unused (=0)
	unsigned long DataOffset; //Offset from beginning of file to the beginning of the bitmap data
} Header;

typedef struct infoheader{
	unsigned long Size; //Size of InfoHeader =40
        unsigned long Width; //Horizontal width of bitmap in pixels
        unsigned long Height; //Vertical height of bitmap in pixels
        unsigned short Planes; //Number of Planes (=1)
        unsigned short BitsPerPixel; /* Bits per Pixel used to store palette entry information. This also identifies in an indirect way the number of possible colors. Possible values are:
					1 = monochrome palette. NumColors = 1  
					4 = 4bit palletized. NumColors = 16  
					8 = 8bit palletized. NumColors = 256 
					16 = 16bit RGB. NumColors = 65536
					24 = 24bit RGB. NumColors = 16M */
        unsigned long Compression; /*Type of Compression  
					0 = BI_RGB   no compression  
					1 = BI_RLE8 8bit RLE encoding  
					2 = BI_RLE4 4bit RLE encoding*/
        unsigned long ImageSize; //(compressed) Size of Image, it is valid to set this =0 if Compression = 0
        unsigned long XpixelsPerM; //horizontal resolution: Pixels/meter
        unsigned long YpixelsPerM; //vertical resolution: Pixels/meter
	unsigned long ColorUsed; //Number of actually used colors. For a 8-bit / pixel bitmap this will be 100h or 256.
        unsigned long ImportantColors; //Number of important colors, 0 = all


} InfoHeader;

typedef struct colortableelement{ //Element of palette - unusued if InfoHeader.BitsPerPixel >= 16
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char reserved; //unused
} ColorTableElement;

typedef struct pixeldataelement{
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
} PixelDataElement;

typedef struct bitmap_palette{
	Header header;
	InfoHeader infoHeader;
	ColorTableElement * colorTable;
	PixelDataElement * pixelData;
} BitMap_Palette;

typedef struct bitmap{
	Header header;
	InfoHeader infoHeader;
	PixelDataElement * pixelData;
} BitMap;

unsigned long BMP_size(int nbOfPixels){ //Returns size of BMP file
    return 54+3*nbOfPixels;
}
