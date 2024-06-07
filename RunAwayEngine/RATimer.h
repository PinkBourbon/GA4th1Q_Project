#pragma once
#include <windows.h>
#include <profileapi.h>
#include "RAType.h"

static LARGE_INTEGER _timerFrequency;
static LARGE_INTEGER _startTime;
static LARGE_INTEGER _endTime;

/// <summary>
/// �ð����� ���� ���� ���ļ� ���� static������ ����
/// </summary>
inline void SetTimerFrequency() 
{
	QueryPerformanceFrequency(&_timerFrequency);
	_timerFrequency.QuadPart /= 1000;
}

/// <summary>
/// ȣ������� �ð��� static������ ����
/// </summary>
inline void StartTimer()
{
	QueryPerformanceCounter(&_startTime);
}

/// <summary>
/// ȣ������� �ð��� static������ �����ϰ� stop - start �ð����� ms�� �����Ѵ�.
/// </summary>
/// <returns></returns>
inline int64 StopTimer()
{
	QueryPerformanceCounter(&_endTime);
	_endTime.QuadPart -= _startTime.QuadPart;
	_endTime.QuadPart /= _timerFrequency.QuadPart;

	return _endTime.QuadPart;
}