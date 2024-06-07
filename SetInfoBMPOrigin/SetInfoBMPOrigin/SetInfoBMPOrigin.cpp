// SetInfoBMPOrigin.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "type.h"

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

/// <summary>
/// 해당 비트맵에 x y 좌표에 b값을 ff로 바꿔주는 함수.
/// </summary>
/// <param name="filePath">파일 경로</param>
/// <param name="x">좌측부터 x만큼 떨어진 위치. 0 ~ filewidth - 1</param>
/// <param name="y">아래부터 y만큼 떨어진 위치. 0 ~ fileHeight - 1</param>
/// <returns></returns>
bool SetBitMap(const char* filePath, int32 x, int32 y)
{
	FILE* pBmp;
	fopen_s(&pBmp, filePath, "rb+");

	if (pBmp == NULL)	// 파일 오픈 실패 시 리턴
	{
		return false;
	}

	BITMAPFILEHEADER fileHeader;	// 파일 헤더
	BITMAPINFOHEADER bitmapHeader;	// 비트맵 정보 헤더	

	fread(&fileHeader, sizeof(fileHeader), 1, pBmp);
	fread(&bitmapHeader, sizeof(bitmapHeader), 1, pBmp);

	if (fileHeader.bfType != 0x4D42)	// 비트맵 파일이 아니면 리턴
	{
		fclose(pBmp);
		return false;
	}

	int32 offset = fileHeader.bfOffBits;
	int32 width = bitmapHeader.biWidth;
	int32 height = bitmapHeader.biHeight;
	int32 pixelSize = bitmapHeader.biBitCount / 8;
	int32 padding = ((bitmapHeader.biWidth) * pixelSize) % 4;
	if (padding != 0)
	{
		padding = 4 - padding;
	}

	if (x >= width || y >= height)
	{
		fclose(pBmp);
		return false;
	}

	int64 fileY = (y);
	fpos_t fileOffset = offset + (pixelSize * (width * fileY + x) + padding * fileY);
	fsetpos(pBmp, &fileOffset);

	uint8 wBuffer = 0xff;
	fwrite(&wBuffer, 1, 1, pBmp);
	fclose(pBmp);
	return true;
}


int main()
{
	SetBitMap("bush02_i.bmp", 75, 75);
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
