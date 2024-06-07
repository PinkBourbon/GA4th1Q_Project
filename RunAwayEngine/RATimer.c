//#pragma once
//#include "Timer.h"
//
//static LARGE_INTEGER _timerFrequency;
//static LARGE_INTEGER _startTime;
//static LARGE_INTEGER _endTime;
//
//
//void SetTimerFrequency()
//{
//	QueryPerformanceFrequency(&_timerFrequency);
//	_timerFrequency.QuadPart /= 1000;
//}
//
//void StartTimer()
//{
//	QueryPerformanceCounter(&_startTime);
//}
//
//int64 StopTimer()
//{
//	QueryPerformanceCounter(&_endTime);
//	_endTime.QuadPart -= _startTime.QuadPart;
//	_endTime.QuadPart /= _timerFrequency.QuadPart;
//
//	return _endTime.QuadPart;
//}
//
