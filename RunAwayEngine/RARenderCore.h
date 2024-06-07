#pragma once

#include <windows.h>

#include "RAType.h"
#include "RARGB.h"

typedef struct _GameObject GameObject;
typedef struct _RACamera RACamera;

/// <summary>
/// �������� ����� ���� ī�޶� �����մϴ�.
/// </summary>
/// <param name="camera">������ ���� ī�޶�</param>
void SetMainCamera(const RACamera* camera);

/// <summary>
/// ������ �ھ �ʱ�ȭ�մϴ�
/// </summary>
/// <param name="hWnd">�ʱ�ȭ�� ����� ������ �ڵ�</param>
/// <param name="screenWidth">ȭ���� �ʺ�</param>
/// <param name="screenHeight">ȭ���� ����</param>
/// <returns></returns>
bool InitializeRenderCore(HWND hWnd, int32 screenWidth, int32 screenHeight);

/// <summary>
/// ������ �ھ �ݽ��ϴ�.
/// </summary>
void CloseRenderCore();

/// <summary>
/// ����ۿ� �� �ȼ��� rgb���� ����.
/// ȭ�鿡 ��� ��� �׸��� ������ ���ĺ����� ������.
/// </summary>
/// <param name="x">������� �ȼ�x ��ǥ</param>
/// <param name="y">������� �ȼ�y ��ǥ</param>
/// <param name="rgb">�׸� rgb ��</param>
void SetPixelToBackBuffer(uint8 layer, int32 objectY, int32 x, int32 y, RARgb rgb);

/// <summary>
/// ����۸� 'ȭ��'�� ����մϴ�.
/// </summary>
void DisplayBackBuffer();

/// <summary>
/// ��Ʈ���� '�����'�� �׸��ϴ�.
/// </summary>
/// <param name="screenLeftX"></param>
/// <param name="screenTopY"></param>
/// <param name="bitmap">�׸� ��Ʈ��</param>
//void RenderGameObjectToBackBuffer(int32 screenLeftX, int32 screenTopY, RARgb* bitmap);

/// <summary>
/// renderTarget�� ����ִ� ��� ���ӿ�����Ʈ�� ����ۿ� �׸��� �Լ�
/// �� ������ 1ȸ�� ȣ��Ǵ� �Լ�.
/// </summary>
/// <param name="gameObject">�� �����ӿ� �ɸ� �ð�</param>
void RenderToBackBuffer(int64 deltaTime);

/// <summary>
/// �׸� ��� �߰��մϴ�.
/// </summary>
void AddRenderTarget(GameObject* gameObject);

/// <summary>
/// �׸� ��󿡼� �����մϴ�.
/// </summary>
void DeleteRenderTarget(GameObject* gameObject);
