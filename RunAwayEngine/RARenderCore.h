#pragma once

#include <windows.h>

#include "RAType.h"
#include "RARGB.h"

typedef struct _GameObject GameObject;
typedef struct _RACamera RACamera;

/// <summary>
/// 렌더링에 사용할 메인 카메라를 지정합니다.
/// </summary>
/// <param name="camera">지정할 메인 카메라</param>
void SetMainCamera(const RACamera* camera);

/// <summary>
/// 렌더링 코어를 초기화합니다
/// </summary>
/// <param name="hWnd">초기화에 사용할 윈도우 핸들</param>
/// <param name="screenWidth">화면의 너비</param>
/// <param name="screenHeight">화면의 높이</param>
/// <returns></returns>
bool InitializeRenderCore(HWND hWnd, int32 screenWidth, int32 screenHeight);

/// <summary>
/// 렌더링 코어를 닫습니다.
/// </summary>
void CloseRenderCore();

/// <summary>
/// 백버퍼에 한 픽셀에 rgb값을 세팅.
/// 화면에 벗어날 경우 그리지 않으며 알파블랜딩을 시행함.
/// </summary>
/// <param name="x">백버퍼의 픽셀x 좌표</param>
/// <param name="y">백버퍼의 픽셀y 좌표</param>
/// <param name="rgb">그릴 rgb 값</param>
void SetPixelToBackBuffer(uint8 layer, int32 objectY, int32 x, int32 y, RARgb rgb);

/// <summary>
/// 백버퍼를 '화면'에 출력합니다.
/// </summary>
void DisplayBackBuffer();

/// <summary>
/// 비트맵을 '백버퍼'에 그립니다.
/// </summary>
/// <param name="screenLeftX"></param>
/// <param name="screenTopY"></param>
/// <param name="bitmap">그릴 비트맵</param>
//void RenderGameObjectToBackBuffer(int32 screenLeftX, int32 screenTopY, RARgb* bitmap);

/// <summary>
/// renderTarget에 들어있는 모든 게임오브젝트를 백버퍼에 그리는 함수
/// 매 프레임 1회씩 호출되는 함수.
/// </summary>
/// <param name="gameObject">한 프레임에 걸린 시간</param>
void RenderToBackBuffer(int64 deltaTime);

/// <summary>
/// 그릴 대상에 추가합니다.
/// </summary>
void AddRenderTarget(GameObject* gameObject);

/// <summary>
/// 그릴 대상에서 제외합니다.
/// </summary>
void DeleteRenderTarget(GameObject* gameObject);
