#pragma once

#include "RARgb.h"
#include "RAType.h"
#include "RAImage.h"

typedef struct _GameObject GameObject;

typedef struct _RAAnimation
{
	int64 elapsedTime;	// 경과 시간
	uint32 frameIntervalMs;	// 프레임 간격 (ms)
	uint16 currentFrameIndex;	// 출력할 프레임 인덱스
	uint16 imageArraySize;	// 이미지 배열 크기
	RAImage** imageArray; // 이미지 배열
}RAAnimation;

// 애니메이션 구조체를 넣으면, 현재 그려야 할 이미지가 튀어나오는 함수
RAImage* GetCurrentFrameBitmap(RAAnimation* this, int64 deltaTime);


// 컨텐츠에 애니메이션을 쓸 수 있게 만드는 함수
bool SetAnimation(RAAnimation* animArray, uint16 animIndex, uint32 frameinterval, uint16 imageCount);

void SetImage(RAAnimation* animArray, uint16 animIndex, uint16 imageIndex, const char* filePath);

void ChangeAnimIndex(GameObject* this, uint16 index);