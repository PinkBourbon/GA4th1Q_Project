#pragma once

#include <windows.h>
#include "RAGameObject.h"

/// <summary>
/// ������ �ʱ�ȭ�մϴ�.
/// </summary>
/// <param name="hWnd">������ �ڵ�</param>
void InitializeEngine(HWND hWnd, int32 screenWidth, int32 screenHeight);

/// <summary>
/// ������ �����մϴ�.
/// </summary>
void CloseEngine();

/// <summary>
/// ���� �����Դϴ�.
/// </summary>
void GameLoop();

/// <summary>
/// ���ӿ�����Ʈ�� �Ҵ�޾� ��Ȱ��ȭ �� ���·� ����Ʈ�� �߰��ϰ� ��ȯ�մϴ�.
/// </summary>
/// <returns></returns>
GameObject* AllocGameObject();

/// <summary>
/// ���ӿ�����Ʈ�� ������Ʈ ����Ʈ���� �����ϰ� �Ҵ������մϴ�.
/// </summary>
/// <param name="gameObject">������ ���ӿ�����Ʈ</param>
void FreeGameObject(GameObject* gameObject);

/// <summary>
/// ���ӿ�����Ʈ�� ���¸� Ȱ��ȭ �մϴ�(start���·� �ٲ�)
/// </summary>
/// <param name="gameObject"></param>
void EnableGameObject(GameObject* gameObject);

/// <summary>
/// ���ӿ�����Ʈ�� ���¸� ��Ȱ��ȭ �մϴ� (disable�� �ٲ�)
/// </summary>
/// <param name="gameObject"></param>
void DisableGameObject(GameObject* gameObject);

/// <summary>
/// ������ ��������ִ� �Լ�
/// </summary>
void ExitGame();
