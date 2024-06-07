#pragma once
#include "RAType.h"

typedef union _RARgb
{
	struct 
	{
		uint8 b;
		uint8 g;
		uint8 r;
		uint8 a;
	}channels;

	uint32 argb;

}RARgb;
