#pragma once

#include <windows.h>
#include "RAGameObject.h"

/// <summary>
/// 엔진을 초기화합니다.
/// </summary>
/// <param name="hWnd">윈도우 핸들</param>
void InitializeEngine(HWND hWnd, int32 screenWidth, int32 screenHeight);

/// <summary>
/// 엔진을 종료합니다.
/// </summary>
void CloseEngine();

/// <summary>
/// 게임 루프입니다.
/// </summary>
void GameLoop();

/// <summary>
/// 게임오브젝트를 할당받아 비활성화 된 상태로 리스트에 추가하고 반환합니다.
/// </summary>
/// <returns></returns>
GameObject* AllocGameObject();

/// <summary>
/// 게임오브젝트를 오브젝트 리스트에서 삭제하고 할당해제합니다.
/// </summary>
/// <param name="gameObject">삭제할 게임오브젝트</param>
void FreeGameObject(GameObject* gameObject);

/// <summary>
/// 게임오브젝트의 상태를 활성화 합니다(start상태로 바뀜)
/// </summary>
/// <param name="gameObject"></param>
void EnableGameObject(GameObject* gameObject);

/// <summary>
/// 게임오브젝트의 상태를 비활성화 합니다 (disable로 바뀜)
/// </summary>
/// <param name="gameObject"></param>
void DisableGameObject(GameObject* gameObject);

/// <summary>
/// 게임을 종료시켜주는 함수
/// </summary>
void ExitGame();
