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

	if (pBmp == NULL)	// 파일 오픈 실패 시 리턴
	{
		return map;
	}

	BITMAPFILEHEADER fileHeader;	// 파일 헤더
	BITMAPINFOHEADER bitmapHeader;	// 비트맵 정보 헤더	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// 비트맵 파일이 아니면 리턴
	{
		fclose(pBmp);
		return map;
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
		return map;
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
	map.width = width;
	map.height = height;
	map.mapArray = mapInfos;

	fclose(pBmp);

	return map;
}

