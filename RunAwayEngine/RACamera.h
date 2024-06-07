#pragma once
#include "RARenderCore.h"
#include "RAGameObject.h"

// ī�޶� �ӽ� ��ǥ
typedef struct _RACamera
{
	int32 posX;
	int32 posY;
	int32 screenPixelWidth;
	int32 screenPixelHeight;
} RACamera;

/// <summary>
/// ī�޶� ����ü�� �����ϴ� �Լ�
/// </summary>
/// <param name="camera">������ ī�޶� ������</param>
/// <param name="screenWidth">ȭ�� �ȼ� �ʺ�</param>
/// <param name="screenHeight">ȭ�� �ȼ� ����</param>
void SetCamera(RACamera* camera, int32 screenWidth, int32 screenHeight);

/// <summary>
/// ���� ��ǥ�� ��ȯ
/// </summary>
/// <param name="camera"></param>
/// <param name="inOutX">X���� �Է��ϸ� �ش� ���� screenX�� ��ȯ�ؼ� ��ȯ</param>
/// <param name="inOutY">X���� �Է��ϸ� �ش� ���� screenX�� ��ȯ�ؼ� ��ȯ</param>
void ViewTransfrom(const RACamera* camera, float* inOutX, float* inOutY);
	
// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ��� �ʿ�
