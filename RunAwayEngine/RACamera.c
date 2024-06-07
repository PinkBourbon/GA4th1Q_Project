#include "RACamera.h"

void SetCamera(RACamera* camera, int32 screenWidth, int32 screenHeight)
{
	camera->screenPixelWidth = screenWidth;
	camera->screenPixelHeight = screenHeight;

	camera->posX = 0;
	camera->posY = 0;
}

void ViewTransfrom(const RACamera* camera ,float* inOutX, float* inOutY)
{
	*inOutX -= (float)camera->posX;
	*inOutY -= (float)camera->posY;
}
