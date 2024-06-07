
#include <stdio.h>
#include <windows.h>

#include "RAGameEngine.h"
#pragma comment(lib, "RunAwayEngine.lib")

#include "RAVector2.h"
#include "RAMatrix2.h"
#include "RAAlphaBlend.h"

#include "RAType.h"
#include "RARGB.h"
#include "RABmpParser.h"



typedef struct _Map
{
	uint16 width;
	uint16 height;
	RARgb* mapArray;
}Map;


void ObjectStart(GameObject* this)
{
	printf("Object Started.\n");

}

void ObjectUpdate(GameObject* this, int64 deltaTime)
{
	printf("%lldms, ", deltaTime);
	//printf("x: %f, y: %f\n", this->posX, this->posY);
}

void PrintMap(Map* map)
{

	// Rä�� �׽�Ʈ
	for (int y = 0; y < map->height; ++y)
	{
		for (int x = 0; x < map->width + 1; ++x)
		{
			if (map->mapArray[y*map->width + x].channels.r == 255)
			{
				printf("1");
			}
			else if (map->mapArray[y * map->width + x].channels.r == 0)
			{
				printf("0");
			}
			else
			{
				printf("%d", map->mapArray[y * map->width + x].channels.r);
			}

		}
		printf("\n");
	}
	printf("\n=======================================================\n\n");

	// Gä�� �׽�Ʈ
	for (int y = 0; y < map->height; ++y)
	{
		for (int x = 0; x < map->width + 1; ++x)
		{
			if (map->mapArray[y * map->width + x].channels.g == 255)
			{
				printf("1");
			}
			else if (map->mapArray[y * map->width + x].channels.g == 0)
			{
				printf("0");
			}
			else
			{
				printf("%d", map->mapArray[y * map->width + x].channels.g);
			}

		}
		printf("\n");
	}
	printf("\n=======================================================\n\n");

	// Bä�� �׽�Ʈ
	for (int y = 0; y < map->height; ++y)
	{
		for (int x = 0; x < map->width + 1; ++x)
		{
			if (map->mapArray[y * map->width + x].channels.b == 255)
			{
				printf("1");
			}
			else if (map->mapArray[y * map->width + x].channels.b == 0)
			{
				printf("0");
			}
			else
			{
				printf("%d", map->mapArray[y * map->width + x].channels.b);
			}

		}
		printf("\n");
	}
	printf("\n=======================================================\n\n");

}

Map ReadMapData(const char* filePath)
{
	FILE* pBmp;
	fopen_s(&pBmp, filePath, "rb");

	if (pBmp == NULL)	// ���� ���� ���� �� ����
	{
		return;
	}

	BITMAPFILEHEADER fileHeader;	// ���� ���
	BITMAPINFOHEADER bitmapHeader;	// ��Ʈ�� ���� ���	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// ��Ʈ�� ������ �ƴϸ� ����
	{
		fclose(pBmp);
		return;
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
		return;
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
	Map map;
	map.width = width;
	map.height = height;
	map.mapArray = mapInfos;

	// map ����ü�� ���� �ʿ��Ѱ�?
	// map ����ü�� ����� 2���� �迭 �����ϴ� �� �³�?
	// �ƴϸ� �׳� ����� �ּҸ� ��� �ִ� �� �³�?

	//memcpy_s(map.mapArray)

	//// 2���� �迭 �����Ҵ� ����
	//for (int i = 0; i < height; i++)
	//{
	//	free(mapInfo[i]);
	//}
	//free(mapInfo);
	fclose(pBmp);

	return map;
}





int main()
{
	Map map;

	//map = ReadMapData("Test_Maze.bmp");
	map = ReadMapData("Test_MazeR.bmp");
	//map = ReadMapData("Test_MazeG.bmp");
	//map = ReadMapData("Test_MazeB.bmp");

	//printf("%08x", (map.mapArray[0]).argb);
	//printf("%d", (map.mapArray[5][5]).g);
	//printf("%d", (map.mapArray[5][5]).b);

	PrintMap(&map);

	return 0;
}