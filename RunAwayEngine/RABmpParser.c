#include "RABmpParser.h"
#include <stdio.h>
#include <malloc.h>
//#include <wingdi.h>

#pragma pack (1)
typedef struct tagBITMAPFILEHEADER {
	uint16    bfType;	// 0x4d42
	uint32   bfSize;	// 파일 크기 (Byte)
	uint16    bfReserved1;	// 항상 0
	uint16    bfReserved2;	// 항상 0
	uint32   bfOffBits;		// 픽셀 데이터 시작 offset
} BITMAPFILEHEADER;

#pragma pack (1)
typedef struct tagBITMAPINFOHEADER {
	uint32      biSize;	// 구조체의 크기
	int32       biWidth;	// 비트맵 가로 길이
	int32       biHeight;	// 비트맵 세로 길이
	uint16       biPlanes;	// 항상 1
	uint16       biBitCount;	// 픽셀당 비트 수
	uint32      biCompression;	// 압축 유형
	uint32      biSizeImage;	// 비트맵 데이터의 크기
	int32       biXPelsPerMeter;// 수평 해상도
	int32       biYPelsPerMeter;// 수직 해상도
	uint32      biClrUsed;		// LUT에 포함된 color index의 개수
	uint32      biClrImportant;	// 비트맵을 화면에 출력하기 위해
} BITMAPINFOHEADER;

#pragma pack (1)
typedef struct tagRGBQUAD {
	uint8    rgbBlue;
	uint8    rgbGreen;
	uint8    rgbRed;
	uint8    rgbReserved;
} RGBQUAD;

RARgb* LoadBitmap2(const char* filePath, int32* outWidth, int32* outHeight)
{
	FILE* pBmp;
	fopen_s(&pBmp, filePath, "rb");

	if (pBmp == NULL)	// 파일 오픈 실패 시 리턴
	{
		return NULL;
	}

	BITMAPFILEHEADER fileHeader;	// 파일 헤더
	BITMAPINFOHEADER bitmapHeader;	// 비트맵 정보 헤더	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// 비트맵 파일이 아니면 리턴
	{
		fclose(pBmp);
		return NULL;
	}

	int32 offset = fileHeader.bfOffBits;
	offset -= sizeof(fileHeader);
	fread(&bitmapHeader, sizeof(bitmapHeader), 1, pBmp);
	offset -= sizeof(bitmapHeader);

	while (offset > 0)
	{
		char temp;
		fread(&temp, sizeof(temp), 1, pBmp);
		offset--;
	}

	int32 pixelSize = bitmapHeader.biBitCount / 8;

	*outWidth = bitmapHeader.biWidth;
	*outHeight = bitmapHeader.biHeight;

	int32 padding = ((bitmapHeader.biWidth) * pixelSize) % 4;
	if (padding != 0)
	{
		padding = 4 - padding;
	}
	int32 imgSize = bitmapHeader.biWidth * bitmapHeader.biHeight * pixelSize + padding * bitmapHeader.biHeight;
	uint8* image = (uint8*)malloc(sizeof(uint8) * imgSize);

	if (image == NULL)	// image malloc 실패 시 리턴
	{
		fclose(pBmp);
		return NULL;
	}

	fread(image, 1, imgSize, pBmp);

	RARgb* result = (RARgb*)malloc(sizeof(RARgb) * imgSize);

	if (result == NULL)	// result malloc 실패 시 리턴
	{
		fclose(pBmp);
		free(image);
		return NULL;
	}

	int32 width = bitmapHeader.biWidth;
	int32 height = bitmapHeader.biHeight;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			result[width * (height - (y + 1)) + x].channels.a = 0x00;
			result[width * (height - (y + 1)) + x].channels.b = image[3 * (width * y + x) + padding * y];
			result[width * (height - (y + 1)) + x].channels.g = image[3 * (width * y + x) + padding * y + 1];
			result[width * (height - (y + 1)) + x].channels.r = image[3 * (width * y + x) + padding * y + 2];
		}
	}

	free(image);
	fclose(pBmp);

	return result;
}

RARgb* LoadInfoBitmap(const char* filePath, RARgb* bitmap, int32* originX, int32* originY)
{
	FILE* pBmp;
	fopen_s(&pBmp, filePath, "rb");

	if (pBmp == NULL)	// 파일 오픈 실패 시 리턴
	{
		return NULL;
	}

	BITMAPFILEHEADER fileHeader;	// 파일 헤더
	BITMAPINFOHEADER bitmapHeader;	// 비트맵 정보 헤더	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// 비트맵 파일이 아니면 리턴
	{
		fclose(pBmp);
		return NULL;
	}

	int32 offset = fileHeader.bfOffBits;
	offset -= sizeof(fileHeader);
	fread(&bitmapHeader, sizeof(bitmapHeader), 1, pBmp);
	offset -= sizeof(bitmapHeader);

	while (offset > 0)
	{
		char temp;
		fread(&temp, sizeof(temp), 1, pBmp);
		offset--;
	}

	int32 pixelSize = bitmapHeader.biBitCount / 8;

	int32 padding = ((bitmapHeader.biWidth) * pixelSize) % 4;
	if (padding != 0)
	{
		padding = 4 - padding;
	}
	int32 imgSize = bitmapHeader.biWidth * bitmapHeader.biHeight * pixelSize + padding * bitmapHeader.biHeight;
	uint8* image = (uint8*)malloc(sizeof(uint8) * imgSize);

	if (image == NULL)	// image malloc 실패 시 리턴
	{
		fclose(pBmp);
		return NULL;
	}

	fread(image, 1, imgSize, pBmp);

	RARgb* result = bitmap;

	if (result == NULL)	// result malloc 실패 시 리턴
	{
		fclose(pBmp);
		free(image);
		return NULL;
	}

	int32 width = bitmapHeader.biWidth;
	int32 height = bitmapHeader.biHeight;

	bool isfindOrigin = false;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// 정보 비트맵의 r채널에서 '알파값'을 가져옴
			result[width * (height - (y + 1)) + x].channels.a = image[3 * (width * y + x) + padding * y + 2];

			// 정보 비트맵의 b채널에서 '기준점 좌표'를 가져옴
			if (image[3 * (width * y + x) + padding * y] == 255)
			{
				if (isfindOrigin == true) // 기준점을 두 개 이상 발견.
				{
					fclose(pBmp);
					free(image);
					return NULL;
				}
				*originX = x;
				*originY = height - y - 1;
				isfindOrigin = true;
			}
		}
	}

	free(image);
	fclose(pBmp);

	if (isfindOrigin == false) // 기준점을 하나도 발견하지 못함.
	{
		return NULL;
	}

	return result;
}
