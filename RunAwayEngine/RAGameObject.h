#pragma once

#include "RAType.h"
#include "RAAnimation.h"

typedef union _RARgb RARgb;
typedef struct _RAAnimation RAAnimation;

typedef enum _eGameObjectState
{
	GameObject_START,
	GameObject_UPDATE,
	GameObject_UPDATE_TO_DISABLE,
	GameObject_NOUPDATE,
	GameObject_DISABLE
}eGameObjectState;

typedef struct _GameObject
{
	uint16 gameObjectID;
	eGameObjectState state;
	bool isLeftDir;
	uint8 layer;
	float posX;
	float posY;
	float rotation;
	float scaleX;
	float scaleY;
	RAAnimation* animArray;
	uint16 animSize;
	uint16 currAnimIndex;

	void(*Start)(struct _GameObject* this);
	void(*Update)(struct _GameObject* this, int64 deltaTime);
	//void(*Render)(struct _GameObject* this, int64 deltaTime);
}GameObject;
