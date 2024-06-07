#pragma once

#include "RARgb.h"
#include "RAType.h"
#include "RAImage.h"

typedef struct _GameObject GameObject;

typedef struct _RAAnimation
{
	int64 elapsedTime;	// ��� �ð�
	uint32 frameIntervalMs;	// ������ ���� (ms)
	uint16 currentFrameIndex;	// ����� ������ �ε���
	uint16 imageArraySize;	// �̹��� �迭 ũ��
	RAImage** imageArray; // �̹��� �迭
}RAAnimation;

// �ִϸ��̼� ����ü�� ������, ���� �׷��� �� �̹����� Ƣ����� �Լ�
RAImage* GetCurrentFrameBitmap(RAAnimation* this, int64 deltaTime);


// �������� �ִϸ��̼��� �� �� �ְ� ����� �Լ�
bool SetAnimation(RAAnimation* animArray, uint16 animIndex, uint32 frameinterval, uint16 imageCount);

void SetImage(RAAnimation* animArray, uint16 animIndex, uint16 imageIndex, const char* filePath);

void ChangeAnimIndex(GameObject* this, uint16 index);