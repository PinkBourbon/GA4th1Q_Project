#include "RARenderCore.h"
#include "RAAnimation.h"
#include "RABitMapPrint.h"
#include "RAGameObject.h"
#include "RAAlphaBlend.h"
#include "RACamera.h"
#include "RASingleList.h"

static HWND _hWnd;
static HDC _screenHDC;
static HDC _backBufferHDC;
static LPDWORD _pPixelBuffer;	// �ָ��� �̸�?

typedef struct _RALayer
{
	uint8 layer;
	uint16 y;
}RALayer;

RALayer* layerArr;

static int32 _screenWidth;
static int32 _screenHeight;

static HBITMAP _bitmap;
static HBITMAP _oldBitmap;

static RANode** _renderTargetLayerArr;
static int32 _renderLayerSize = 7;
static RACamera* _mainCamera;

void SetMainCamera(const RACamera* camera)
{
	_mainCamera = (RACamera*)camera;
}

bool InitializeRenderCore(HWND hWnd, int32 screenWidth, int32 screenHeight)
{
	_renderTargetLayerArr = (RANode**)malloc(sizeof(RANode*) * _renderLayerSize);

	if (_renderTargetLayerArr == NULL)
	{
		return false;
	}

	for (int32 i = 0; i < _renderLayerSize; ++i)
	{
		*(_renderTargetLayerArr + i) = MakeNewList();
	}

	_hWnd = hWnd;	// ������ �ڵ�

	_screenWidth = screenWidth;	// ��ũ�� �ʺ�
	_screenHeight = screenHeight;	// ��ũ�� ����

	_screenHDC = GetDC(_hWnd);	// ��ũ�� DC
	_backBufferHDC = CreateCompatibleDC(_screenHDC);	// ����� DC

	// DIBSection�� ����� ���� BITMAPINFO ����
	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = _screenWidth;
	bmpInfo.bmiHeader.biHeight = _screenHeight;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	_bitmap = CreateDIBSection(_screenHDC, &bmpInfo, DIB_RGB_COLORS, (void**)&_pPixelBuffer, NULL, 0);
	if (_bitmap == NULL)
	{
		ReleaseDC(_hWnd, _screenHDC);
		return false;
	}
	_oldBitmap = SelectObject(_backBufferHDC, _bitmap);

	layerArr = (RALayer*)malloc(sizeof(RALayer) * _screenWidth * _screenHeight);

	return true;
}

void CloseRenderCore()
{

	for (int32 i = 0; i < _renderLayerSize; ++i)
	{
		DeleteList(_renderTargetLayerArr[i]);
	}

	free(_renderTargetLayerArr);

	SelectObject(_backBufferHDC, _oldBitmap);
	DeleteObject(_bitmap);
	ReleaseDC(_hWnd, _screenHDC);
}

void PrintImage(RAImage* image, uint8 layer, int32 objecY, int32 x, int32 y)
{
	int32 height = image->height;
	if (height + y > _screenHeight)
	{
		height = _screenHeight - y;
	}

	int32 width = image->width;
	if (width + x >= _screenWidth)
	{
		width = _screenWidth - x;
	}

	int32 startI = 0;
	if (y < 0)
	{
		startI = y * -1;
	}
	int32 startJ = 0;
	if (x < 0)
	{
		startJ = x * -1;
	}

	for (int32 i = startI; i < height; i++)
	{
		for (int32 j = startJ; j < width; j++)
		{
			SetPixelToBackBuffer(layer, objecY, j + x, i + y, image->bitmap[image->width * i + j]);
		}
	}
}

void PrintImageMirror(RAImage* image, uint8 layer, int32 objectY, int32 x, int32 y)
{
	int32 height = image->height;
	if (height + y > _screenHeight)
	{
		height = _screenHeight - y;
	}

	int32 width = image->width;
	if (width + x >= _screenWidth)
	{
		width = _screenWidth - x;
	}

	int32 startI = 0;
	if (y < 0)
	{
		startI = y * -1;
	}
	int32 startJ = 0;
	if (x < 0)
	{
		startJ = x * -1;
	}

	for (int32 i = startI; i < height; i++)
	{
		for (int32 j = startJ; j < width; j++)
		{
			SetPixelToBackBuffer(layer, objectY, j + x, i + y, image->bitmap[width * i + (width - j - 1)]);
		}
	}
}

__forceinline void SetPixelToBackBuffer(uint8 layer, int32 objectY, int32 x, int32 y, RARgb rgb)
{
	int32 index = (_screenHeight - 1 - y) * _screenWidth + x;

	if (layer < layerArr[index].layer)
	{
		return;
	}

	// ���� ���� ������ ���� �ʾ� ����� ��
	// �ߴ��� �������� ����
	if (layer == layerArr[index].layer && objectY < layerArr[index].y)
	{
		return;
	}

	RARgb bufferRgb;
	bufferRgb.argb = _pPixelBuffer[index];

	if (rgb.channels.a == 0xFF)	//���� ������ ���� �޸𸮿� ������ �ʿ䵵 ���� ����.
	{
		return;
	}
	else if (rgb.channels.a != 0x00)	// ������ ������ ��쿡 ���ĺ���. 0xFF ���� ����
	{
		rgb = RAAlphaBlend(rgb, bufferRgb);
	}
	else // �ش� �ȼ��� �������� ��쿡�� ���� ������ ��ġ�� ��� �� ( ����� ������ ���̿� �������� ���� ��쿡 ���� �߻��� -> ������ �����ع���.)
	{
		layerArr[index].layer = layer;
		layerArr[index].y = objectY;
	}
	_pPixelBuffer[index] = rgb.argb;
}

void DisplayBackBuffer()
{
	int32 screenSize = _screenWidth * _screenHeight;
	BitBlt(_screenHDC, 0, 0, _screenWidth, _screenHeight, _backBufferHDC, 0, 0, SRCCOPY);
	memset(_pPixelBuffer, 0, screenSize * sizeof(*_pPixelBuffer));
	memset(layerArr, 0, screenSize * sizeof(*layerArr));
}

static void RenderImageToBackBuffer(GameObject* gameObject, int64 deltaTime)
{
	RAImage* image = GetCurrentFrameBitmap(&(gameObject->animArray[gameObject->currAnimIndex]), deltaTime);

	// �̹����� �׸��� ������ ��ġ�� ���� ī�޶� ��ǥ�� ĳ���� ��ǥ�� ���� ���
	int32 screenLeftX = (int32)(gameObject->posX - image->originX - _mainCamera->posX);
	int32 screenTopY = (int32)(gameObject->posY - image->originY - _mainCamera->posY);

	// �׸� �׸��� ȭ�鿡 ���Ե��� �ʴ´ٸ� �׸��� �ʴ´�.
	if (screenLeftX + image->width < 0 || screenLeftX >= _screenWidth ||
		screenTopY + image->height < 0 || screenTopY >= _screenHeight)
	{
		return;
	}

	//�ش� ������Ʈ�� ���⿡ ���缭 �׸���.
	if (gameObject->isLeftDir)
	{
		PrintImage(image, gameObject->layer, (int32)gameObject->posY, screenLeftX, screenTopY);
	}
	else
	{
		PrintImageMirror(image, gameObject->layer, (int32)gameObject->posY, screenLeftX, screenTopY);
	}
}

void RenderToBackBuffer(int64 deltaTime)
{
	for (int i = 0; i < _renderLayerSize; ++i)
	{
		RANode* currNode = _renderTargetLayerArr[i]->next;
		while (currNode != NULL)
		{
			GameObject* gameObject = (GameObject*)(currNode->data);
			RenderImageToBackBuffer(gameObject, deltaTime);

			currNode = currNode->next;
		}
	}
}

void AddRenderTarget(GameObject* gameObject)
{
	AddNode(_renderTargetLayerArr[gameObject->layer], gameObject);
}

void DeleteRenderTarget(GameObject* gameObject)
{
	DeleteNode(_renderTargetLayerArr[gameObject->layer], gameObject);
}