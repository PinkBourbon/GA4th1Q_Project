#include <stdio.h>
#include <windows.h>

#include "ReadMapData.h"
#include "RARGB.h"

Map ReadMapData(const char* filePath)
{
	Map map;
	map.width = 0;
	map.height = 0;
	map.mapArray = NULL;

	FILE* pBmp;
	fopen_s(&pBmp, filePath, "rb");

	if (pBmp == NULL)	// ���� ���� ���� �� ����
	{
		return map;
	}

	BITMAPFILEHEADER fileHeader;	// ���� ���
	BITMAPINFOHEADER bitmapHeader;	// ��Ʈ�� ���� ���	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// ��Ʈ�� ������ �ƴϸ� ����
	{
		fclose(pBmp);
		return map;
	}

	// ��Ʈ�� ������ ���������� �̵�
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

	// �ȼ� ������(Byte)
	int32 pixelSize = bitmapHeader.biBitCount / 8;

	// ���� �е� ũ�� ���
	int32 padding = ((bitmapHeader.biWidth) * pixelSize) % 4;
	if (padding != 0)
	{
		padding = 4 - padding;
	}

	int32 width = bitmapHeader.biWidth;
	int32 height = bitmapHeader.biHeight;

	// �� ������ ���� 2���� �迭 �����Ҵ�
	RARgb* mapInfos = (RARgb*)malloc(sizeof(RARgb) * height * width);

	if (mapInfos == NULL)
	{
		fclose(pBmp);
		return map;
	}

	// 2���� �迭 �ʱ�ȭ
	for (int y = height - 1; y >= 0; --y) // ���Ϲ����Ǿ������Ƿ� �Ʒ��������� �д´�.
	{
		for (int x = 0; x < width + padding; ++x)
		{
			if (x <= width - 1) // ���� �ȼ��� ���
			{
				fread(&(mapInfos[y * width + x].channels.b), 1, 1, pBmp);
				fread(&(mapInfos[y * width + x].channels.g), 1, 1, pBmp);
				fread(&(mapInfos[y * width + x].channels.r), 1, 1, pBmp);
				mapInfos[y * width + x].channels.a = 0x00;
			}
			else // ���� �е��� ���
			{
				uint8 padding;
				fread(&padding, 1, 1, pBmp);
			}
		}
	}

	// Map ����ü�� �������� �־���
	map.width = width;
	map.height = height;
	map.mapArray = mapInfos;

	fclose(pBmp);

	return map;
}

