
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

	// R채널 테스트
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

	// G채널 테스트
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

	// B채널 테스트
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

	if (pBmp == NULL)	// 파일 오픈 실패 시 리턴
	{
		return;
	}

	BITMAPFILEHEADER fileHeader;	// 파일 헤더
	BITMAPINFOHEADER bitmapHeader;	// 비트맵 정보 헤더	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// 비트맵 파일이 아니면 리턴
	{
		fclose(pBmp);
		return;
	}

	// 비트맵 데이터 시작점까지 이동
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

	// 픽셀 사이즈(Byte)
	int32 pixelSize = bitmapHeader.biBitCount / 8;

	// 라인 패딩 크기 계산
	int32 padding = ((bitmapHeader.biWidth) * pixelSize) % 4;
	if (padding != 0)
	{
		padding = 4 - padding;
	}

	int32 width = bitmapHeader.biWidth;
	int32 height = bitmapHeader.biHeight;

	// 맵 정보를 담을 2차원 배열 동적할당
	RARgb* mapInfos = (RARgb*)malloc(sizeof(RARgb) * height * width);

	if (mapInfos == NULL)
	{
		fclose(pBmp);
		return;
	}

	// 2차원 배열 초기화
	for (int y = height - 1; y >= 0; --y) // 상하반전되어있으므로 아래에서부터 읽는다.
	{
		for (int x = 0; x < width + padding; ++x)
		{
			if (x <= width - 1) // 실제 픽셀일 경우
			{
				fread(&(mapInfos[y * width + x].channels.b), 1, 1, pBmp);
				fread(&(mapInfos[y * width + x].channels.g), 1, 1, pBmp);
				fread(&(mapInfos[y * width + x].channels.r), 1, 1, pBmp);
				mapInfos[y * width + x].channels.a = 0x00;
			}
			else // 라인 패딩일 경우
			{
				uint8 padding;
				fread(&padding, 1, 1, pBmp);
			}
		}
	}

	// Map 구조체에 정보들을 넣어줌
	Map map;
	map.width = width;
	map.height = height;
	map.mapArray = mapInfos;

	// map 구조체가 과연 필요한가?
	// map 구조체의 멤버로 2차원 배열 복사하는 게 맞나?
	// 아니면 그냥 멤버가 주소만 들고 있는 게 맞나?

	//memcpy_s(map.mapArray)

	//// 2차원 배열 동적할당 해제
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