#pragma once
#include "RAType.h"
#include "RARGB.h"

//typedef struct _RARgb RARgb;

/// <summary>
/// 메모리에 비트맵 파일을 로드하는 함수
/// </summary>
/// <param name="filePath">파일 경로(이름 포함)</param>
/// <param name="outWidth">출력용 변수 해당 비트맵의 너비</param>
/// <param name="outHeight">출력용 변수 해당 비트맵의 높이</param>
/// <returns>문제가 생겼을 경우 NULL을 리턴</returns>
RARgb* LoadBitmap2(const char* filePath, int32* outWidth, int32* outHeight);

/// <summary>
/// 로드한 비트맵에 정보용 비트맵을 읽어 정보를 추가하는 함수
/// </summary>
/// <param name="filePath">파일 경로(이름 포함)</param>
/// <param name="bitmap">출력용 변수 로드된 비트맵 이미지 포인터</param>
/// <param name="originX">출력용 변수 해당 비트맵의 기준 x좌표</param>
/// <param name="originY">출력용 변수 해당 비트맵의 기준 y 좌표</param>
/// <returns>정보 파일에 문제가 있을경우 NULL을 리턴</returns>
RARgb* LoadInfoBitmap(const char* filePath, RARgb* bitmap, int32* originX, int32* originY);
