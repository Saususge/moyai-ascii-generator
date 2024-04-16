#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PIXEL_SIZE   3    // size of pixel (24bit bmp)
#define PIXEL_ALIGN  4    
#pragma pack(push, 1) 

// got bmp struct info from below link (ms doc)
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmap

typedef struct BitmapFileHeader
{
    unsigned short bfType;           // BMP magic num
    unsigned int   bfSize;           // file size
    unsigned short bfReserved1;      // reserved (should be zero)
    unsigned short bfReserved2;      
    unsigned int   bfOffBits;        // start of bitmap image data
} BitmapFileHeader;

typedef struct BitmapInfoHeader
{
    unsigned int   biSize;           // size of current struct
    int            biWidth;          // width of img
    int            biHeight;         // height of img
    unsigned short biPlanes;         // color plane nums
    unsigned short biBitCount;       // bit nums for a pixel
    unsigned int   biCompression;    // compression type
    unsigned int   biSizeImage;      // pixel data size of img
    int            biXPelsPerMeter;  // X resolution (pixel per meter)
    int            biYPelsPerMeter;  // Y resolution (pixel per meter)
    unsigned int   biClrUsed;        // nums of used color on plane
    unsigned int   biClrImportant;   // nums of index for bitmap img
} BitmapInfoHeader;

typedef struct RGBTriple
{
    unsigned char rgbtBlue;          // B
    unsigned char rgbtGreen;         // G
    unsigned char rgbtRed;           // R
} RGBTriple;

#pragma pack(pop)

int main(void)
{
    srand(time(NULL)); // setting rand seed to time

    // moyai img file random namer
    int r_num = rand() % 144 + 1;
    char directory[30] = "moyai/";
    char file_num [5];
    sprintf(file_num, "%d", r_num);
    strcat(directory, file_num);
    strcat(directory, ".bmp");
	
    FILE* fpBmp;
    FILE* fpTxt;
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    unsigned char* image;
    int size;
    int width, height;
    int padding;
	
    char ascii[] = { '#', '#', '@', '%', '=', '+', '*', '^', ':' , ';', '-', '`', '"', '.', ' ' };    // letters for drawing

    fpBmp = fopen(directory, "rb");

    fread(&fileHeader, sizeof(BitmapFileHeader), 1, fpBmp);
    fread(&infoHeader, sizeof(BitmapInfoHeader), 1, fpBmp);

    size = infoHeader.biSizeImage;    // pixel data size
    width = infoHeader.biWidth;       // width size of img
    height = infoHeader.biHeight;     // height size of img

    // calculating padding size
    padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

    if (size == 0)    // getting padding size when pixel size is 0
        {
            size = (width * PIXEL_SIZE + padding) * height;
        }

    image = malloc(size);  

    // move file pointer to starting point of pixel data
    fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

    if (fread(image, size, 1, fpBmp) < 1)
	{
            fclose(fpBmp);
            return 0;
	}

    fclose(fpBmp);

    fpTxt = fopen("ascii.txt", "w"); 

    // loop y * x times (height * width)
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
           
            int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);

	    // convert current pixel address to RGBtriple pointer and save it
            RGBTriple *pixel = (RGBTriple *)&image[index];

            // get color from rgb struct
            unsigned char blue = pixel->rgbtBlue;
            unsigned char green = pixel->rgbtGreen;
            unsigned char red = pixel->rgbtRed;

            // get grayscale
            unsigned char gray = (red + green + blue) / PIXEL_SIZE;

            // get ascii array index
            char c = ascii[gray * sizeof(ascii) / 256];

            // save twice
	    // because ascii art is too weird when it saves only once
            fprintf(fpTxt, "%c%c", c, c);
        }

        fprintf(fpTxt, "\n");
    }

    fclose(fpTxt);
    char c;
    fpTxt = fopen("ascii.txt", "r");
	
    // print in console
    while ((c = fgetc(fpTxt)) != EOF) {
    printf("%c", c);
}
    fclose(fpTxt);

    free(image);

    return 0;
}
