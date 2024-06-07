#pragma once
#include <windows.h>
#include <profileapi.h>
#include "RAType.h"

static LARGE_INTEGER _timerFrequency;
static LARGE_INTEGER _startTime;
static LARGE_INTEGER _endTime;

/// <summary>
/// 시간값을 구할 단위 주파수 값을 static변수에 저장
/// </summary>
inline void SetTimerFrequency() 
{
	QueryPerformanceFrequency(&_timerFrequency);
	_timerFrequency.QuadPart /= 1000;
}

/// <summary>
/// 호출시점의 시간을 static변수에 저장
/// </summary>
inline void StartTimer()
{
	QueryPerformanceCounter(&_startTime);
}

/// <summary>
/// 호출시점의 시간을 static변수에 저장하고 stop - start 시간값을 ms로 리턴한다.
/// </summary>
/// <returns></returns>
inline int64 StopTimer()
{
	QueryPerformanceCounter(&_endTime);
	_endTime.QuadPart -= _startTime.QuadPart;
	_endTime.QuadPart /= _timerFrequency.QuadPart;

	return _endTime.QuadPart;
}