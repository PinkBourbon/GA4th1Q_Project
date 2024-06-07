// RATestWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <stdio.h>

#include "framework.h"
#include "RATestWindows.h"

#include "RAType.h"
#include "RAAlphaBlend.h"
#include "RARGB.h"
#include "RABmpParser.h"
#include "RABitMapPrint.h"
#include "RAGameEngine.h"
#include "RARenderCore.h"
#include "RAGameObject.h"
#include "RAImage.h"
#include "RAMacro.h"

#pragma comment(lib, "RunAwayEngine.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

extern g_deltaTime;

void ObjectStart(GameObject* this);
void ObjectUpdate(GameObject* this, int64 deltaTime);
void ObjectRender(GameObject* this);

bool** ReadMapData(const char* filepath);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_RATESTWINDOWS, szWindowClass, MAX_LOADSTRING);

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RATESTWINDOWS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RATESTWINDOWS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 1920, 1080, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	InitializeEngine(hWnd, 1000, 500);
	InitializeRenderCore(hWnd, 1920, 1080);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RATESTWINDOWS));
	MSG msg;


	RAImage* image1 = LoadImage2("Ghost_a.bmp");
	RAImage* image2 = LoadImage2("Ghost_a.bmp");
	RAImage* image3 = LoadImage2("hiking.bmp");
	//RAImage* image1 = LoadImage2("CharactorAmin1_a.bmp");
	//RAImage* image2 = LoadImage2("CharactorAmin2_a.bmp");

	Assert(image1, "이미지 1은 널이면 안됩니다.");
	Assert(image2, "이미지 2는 널이면 안됩니다.");

	RAAnimation animation;

	animation.elapsedTime = 0;
	animation.imageArraySize = 2;
	animation.currentFrameIndex = 0;
	animation.frameIntervalMs = 100;
	animation.imageArray[0] = image1;
	animation.imageArray[1] = image2;
	animation.imageArray[2] = image3;




	GameObject* object1 = AllocGameObject();
	object1->animation = &animation;
	object1->Start = ObjectStart;
	object1->Update = ObjectUpdate;
	object1->Render = ObjectRender;

	EnableGameObject(object1);

	GameLoop();

	CloseRenderCore();

	return 0;
}



void ObjectStart(GameObject* this)
{
	this->posX = 1000;
	this->posY = 100;

	ReadMapData("Test_Maze.bmp");

}

void ObjectUpdate(GameObject* this, int64 deltaTime)
{
	//this->posX -= 1;
}

void ObjectRender(GameObject* this, int64 deltaTime)
{
	PrintAnimation(this->animation, this->posX, this->posY, deltaTime);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}

bool** ReadMapData(const char* filePath)
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

	// 이미지의 총 크기: 가로 픽셀 수 * 세로 픽셀 수 * 1픽셀의 크기 + 라인패딩
	int32 imgSize = width * height * pixelSize + padding * bitmapHeader.biHeight;

	// 맵 정보를 담을 2차원 배열 동적할당
	bool** mapInfo = (bool**)malloc(sizeof(bool*) * height);

	if (mapInfo == NULL)
	{
		fclose(pBmp);
		return NULL;
	}

	for (int i = 0; i < height; i++)
	{
		mapInfo[i] = malloc(sizeof(bool) * width);
		if (mapInfo[i] == NULL)
		{
			fclose(pBmp);
			return NULL;
		}
	}

	// 2차원 배열 초기화
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			fread(&mapInfo[y][x], 1, 1, pBmp);

			//result[width * (height - (y + 1)) + x].channels.a = 0x00;
			//result[width * (height - (y + 1)) + x].channels.b = image[3 * (width * y + x) + padding * y];
			//result[width * (height - (y + 1)) + x].channels.g = image[3 * (width * y + x) + padding * y + 1];
			//result[width * (height - (y + 1)) + x].channels.r = image[3 * (width * y + x) + padding * y + 2];
		}
	}



	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (mapInfo[y][x] == true)
			{
				printf("0");
			}
			else if (mapInfo[y][x] == false)
			{
				printf("1");
			}
		}
		printf("\n");
	}



	int c = 0;
	//// 순서 수정(?)
	//for (int y = 0; y < height; ++y)
	//{
	//	for (int x = 0; x < width; ++x)
	//	{
	//		result[width * (height - (y + 1)) + x].channels.a = 0x00;
	//		result[width * (height - (y + 1)) + x].channels.b = image[3 * (width * y + x) + padding * y];
	//		result[width * (height - (y + 1)) + x].channels.g = image[3 * (width * y + x) + padding * y + 1];
	//		result[width * (height - (y + 1)) + x].channels.r = image[3 * (width * y + x) + padding * y + 2];
	//	}
	//}


	//// 2차원 배열 할당해제
	//for (int i = 0; i < height; i++)
	//{
	//	free(mapInfo[i]);
	//}
	//free(mapInfo);
	
	// 파일 닫기
	fclose(pBmp);

	return mapInfo;
}