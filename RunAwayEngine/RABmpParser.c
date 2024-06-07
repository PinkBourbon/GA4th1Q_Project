#include "RABmpParser.h"
#include <stdio.h>
#include <malloc.h>
//#include <wingdi.h>

#pragma pack (1)
typedef struct tagBITMAPFILEHEADER {
	uint16    bfType;	// 0x4d42
	uint32   bfSize;	// ���� ũ�� (Byte)
	uint16    bfReserved1;	// �׻� 0
	uint16    bfReserved2;	// �׻� 0
	uint32   bfOffBits;		// �ȼ� ������ ���� offset
} BITMAPFILEHEADER;

#pragma pack (1)
typedef struct tagBITMAPINFOHEADER {
	uint32      biSize;	// ����ü�� ũ��
	int32       biWidth;	// ��Ʈ�� ���� ����
	int32       biHeight;	// ��Ʈ�� ���� ����
	uint16       biPlanes;	// �׻� 1
	uint16       biBitCount;	// �ȼ��� ��Ʈ ��
	uint32      biCompression;	// ���� ����
	uint32      biSizeImage;	// ��Ʈ�� �������� ũ��
	int32       biXPelsPerMeter;// ���� �ػ�
	int32       biYPelsPerMeter;// ���� �ػ�
	uint32      biClrUsed;		// LUT�� ���Ե� color index�� ����
	uint32      biClrImportant;	// ��Ʈ���� ȭ�鿡 ����ϱ� ����
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

	if (pBmp == NULL)	// ���� ���� ���� �� ����
	{
		return NULL;
	}

	BITMAPFILEHEADER fileHeader;	// ���� ���
	BITMAPINFOHEADER bitmapHeader;	// ��Ʈ�� ���� ���	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// ��Ʈ�� ������ �ƴϸ� ����
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

	if (image == NULL)	// image malloc ���� �� ����
	{
		fclose(pBmp);
		return NULL;
	}

	fread(image, 1, imgSize, pBmp);

	RARgb* result = (RARgb*)malloc(sizeof(RARgb) * imgSize);

	if (result == NULL)	// result malloc ���� �� ����
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

	if (pBmp == NULL)	// ���� ���� ���� �� ����
	{
		return NULL;
	}

	BITMAPFILEHEADER fileHeader;	// ���� ���
	BITMAPINFOHEADER bitmapHeader;	// ��Ʈ�� ���� ���	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// ��Ʈ�� ������ �ƴϸ� ����
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

	if (image == NULL)	// image malloc ���� �� ����
	{
		fclose(pBmp);
		return NULL;
	}

	fread(image, 1, imgSize, pBmp);

	RARgb* result = bitmap;

	if (result == NULL)	// result malloc ���� �� ����
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
			// ���� ��Ʈ���� rä�ο��� '���İ�'�� ������
			result[width * (height - (y + 1)) + x].channels.a = image[3 * (width * y + x) + padding * y + 2];

			// ���� ��Ʈ���� bä�ο��� '������ ��ǥ'�� ������
			if (image[3 * (width * y + x) + padding * y] == 255)
			{
				if (isfindOrigin == true) // �������� �� �� �̻� �߰�.
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

	if (isfindOrigin == false) // �������� �ϳ��� �߰����� ����.
	{
		return NULL;
	}

	return result;
}
