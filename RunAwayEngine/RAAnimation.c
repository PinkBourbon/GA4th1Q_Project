#include "RAAnimation.h"
#include <malloc.h>
#include "RAGameObject.h"
#include "RAMacro.h"

RAImage* GetCurrentFrameBitmap(RAAnimation* this, int64 deltaTime)
{
	this->elapsedTime += deltaTime;	// �ִϸ��̼� ���� �ð��� ������

	while (this->elapsedTime > this->frameIntervalMs)	// ������ ������ ������ ������
	{
		this->elapsedTime -= this->frameIntervalMs;
		this->currentFrameIndex = (this->currentFrameIndex + 1) % this->imageArraySize; // ���� ���������� �ѱ�. �ٵ� ArraySize�� ���� �ʰ�.
	}

	return this->imageArray[this->currentFrameIndex];
}

bool SetAnimation(RAAnimation* animArray, uint16 animIndex, uint32 frameinterval, uint16 imageCount)
{
	
	animArray[animIndex].elapsedTime = 0;
	animArray[animIndex].frameIntervalMs = frameinterval;
	animArray[animIndex].currentFrameIndex = 0;
	animArray[animIndex].imageArraySize = imageCount;
	animArray[animIndex].imageArray = (RAImage**)malloc(sizeof(RAImage*) * imageCount);

	if (animArray->imageArray == nullptr)
	{
		return false;
	}
	return true;
}

void SetImage(RAAnimation* animArray, uint16 animIndex, uint16 imageIndex, const char* filePath)
{
	animArray[animIndex].imageArray[imageIndex] = LoadImage2(filePath);
	if (animArray[animIndex].imageArray[imageIndex] == NULL)
	{
		Crash();
	}
}

void ChangeAnimIndex(GameObject* this, uint16 index)
{
	if (this->animSize <= index)
	{
		Crash();
	}

	this->currAnimIndex = index;
	this->animArray[index].elapsedTime = 0;
	this->animArray[index].currentFrameIndex = 0;
}
