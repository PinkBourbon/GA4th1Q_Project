#pragma once
#include "RARenderCore.h"
#include "RAGameObject.h"

// 카메라 임시 좌표
typedef struct _RACamera
{
	int32 posX;
	int32 posY;
	int32 screenPixelWidth;
	int32 screenPixelHeight;
} RACamera;

/// <summary>
/// 카메라 구조체를 세팅하는 함수
/// </summary>
/// <param name="camera">세팅할 카메라 포인터</param>
/// <param name="screenWidth">화면 픽셀 너비</param>
/// <param name="screenHeight">화면 픽셀 높이</param>
void SetCamera(RACamera* camera, int32 screenWidth, int32 screenHeight);

/// <summary>
/// 실제 좌표로 변환
/// </summary>
/// <param name="camera"></param>
/// <param name="inOutX">X값을 입력하면 해당 값을 screenX로 변환해서 반환</param>
/// <param name="inOutY">X값을 입력하면 해당 값을 screenX로 변환해서 반환</param>
void ViewTransfrom(const RACamera* camera, float* inOutX, float* inOutY);
	
// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산 필요
