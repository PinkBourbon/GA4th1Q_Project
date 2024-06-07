#pragma once
#include "RARGB.h"
#include "RAType.h"

typedef struct _RAImage
{
	RARgb* bitmap;
	int32 width;
	int32 height;
	int32 originX;
	int32 originY;
} RAImage;

RAImage* LoadImage2(const char* filePath);