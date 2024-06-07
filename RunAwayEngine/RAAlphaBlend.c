//#include "RAAlphaBlend.h"

//RARgb RAAlphaBlend(RARgb upperColor, RARgb lowerColor)
//{
//	uint32 max = 255;
//	uint32 upperA = max - upperColor.channels.a;
//
//	RARgb mixRGB;
//
//	mixRGB.channels.r = (uint8)((uint32)upperColor.channels.r * upperA / max + (uint32)lowerColor.channels.r * (max - upperA) / max);
//	mixRGB.channels.g = (uint8)((uint32)upperColor.channels.g * upperA / max + (uint32)lowerColor.channels.g * (max - upperA) / max);
//	mixRGB.channels.b = (uint8)((uint32)upperColor.channels.b * upperA / max + (uint32)lowerColor.channels.b * (max - upperA) / max);
//
//	//mixRGB.argb = (upperColor.argb * upperA / max) + (lowerColor.argb * (255 - upperA) / max);
//
//	return mixRGB;
//}