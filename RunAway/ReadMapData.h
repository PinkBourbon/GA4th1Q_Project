#pragma once
#include "RAType.h"

typedef union _RARgb RARgb;

typedef struct _Map
{
	uint16 width;
	uint16 height;
	RARgb* mapArray;
}Map;

Map ReadMapData(const char* filePath);