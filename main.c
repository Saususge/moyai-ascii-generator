#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#pragma pack(push, 1) 

typedef struct BitmapFileHeader
{
	unsigned short bfType;           // BMP 파일 매직 넘버
    unsigned int   bfSize;           // 파일 크기
    unsigned short bfReserved1;      // 예약
    unsigned short bfReserved2;      // 예약
    unsigned int   bfOffBits;        // 비트맵 데이터의 시작 위치
} BitmapFileHeader;

typedef struct BitmapInfoHeader
{
	unsigned int   biSize;           // 현재 구조체의 크기
    int            biWidth;          // 비트맵 이미지의 가로 크기
    int            biHeight;         // 비트맵 이미지의 세로 크기
    unsigned short biPlanes;         // 사용하는 색상판의 수
    unsigned short biBitCount;       // 픽셀 하나를 표현하는 비트 수
    unsigned int   biCompression;    // 압축 방식
    unsigned int   biSizeImage;      // 비트맵 이미지의 픽셀 데이터 크기
    int            biXPelsPerMeter;  // 그림의 가로 해상도(미터당 픽셀)
    int            biYPelsPerMeter;  // 그림의 세로 해상도(미터당 픽셀)
    unsigned int   biClrUsed;        // 색상 테이블에서 실제 사용되는 색상 수
    unsigned int   biClrImportant;   // 비트맵을 표현하기 위해 필요한 색상 인덱스 수
} BitmapInfoHeader;

typedef struct RGBTriple
{
	unsigned char rgbtBlue;          // 파랑
    unsigned char rgbtGreen;         // 초록
    unsigned char rgbtRed;           // 빨강
} RGBTriple;

int main(void)
{
	srand(time(NULL));
	int img_arr[1024];
	int r_num = rand() % 144 + 1;
	char directory[30] = "moyai/";
	char file_num [5];
	sprintf(file_num, "%d", r_num);
	strcat(directory, file_num);
	strcat(directory, ".bmp");
	
	FILE* img_file = fopen(directory, "rb");

	

	fclose(img_file);
}
