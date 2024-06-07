#include <malloc.h>
#include "RAImage.h"
#include "RABmpParser.h"
#include "string.h"
#include "RAMacro.h"

//네이밍 변경 필수
RAImage* LoadImage2(const char* filePath)
{
	char path[260];

	strcpy_s(path, sizeof(path), filePath);

	RAImage* image;
	image = (RAImage*)malloc(sizeof(RAImage));
	
	if (image == NULL)
	{
		return NULL;
	}

	image->bitmap = LoadBitmap2(path, &(image->width), &(image->height));
	if (image->bitmap == NULL)
	{
		return NULL;
	}

	for (int i = 5; i < sizeof(path); ++i)
	{
		if (path[i] == '\0')
		{ //a_r.bmp // a_i.bmp
			path[i - 5] = 'i';
			break;
		}
	}

	RARgb* ret = LoadInfoBitmap(path, image->bitmap, &(image->originX), &(image->originY));
	
	//Assert(ret == NULL, "InfoBitmap이 null입니다.");
	if (ret == NULL)
	{
		free(image->bitmap);
		free(image);
		return NULL;
	}
	return image;
}