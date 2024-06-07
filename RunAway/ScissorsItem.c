#include "StoryItem0.h"

#include "RAGameEngine.h"
#include "RAInput.h"
#include "RAAnimation.h"
#include "RACamera.h"
#include "RAVector2.h"
#include "RAType.h"
#include "define.h"

#define ITEM_POS_X (3975)
#define ITEM_POS_Y (7425)

extern bool g_isOnMenu;
extern bool g_isPlayerViewStory;

static bool _isAlreadyGet;
static bool _isNowDrop;
static bool _isDroped;

static RACamera* _camera;
static GameObject* _player;
static GameObject* _scissorsItem;

static float prevPosX;
static float prevPosY;

static Start(GameObject* this)
{
	_scissorsItem->posX = ITEM_POS_X;
	_scissorsItem->posY = ITEM_POS_Y;
	_scissorsItem->isLeftDir = true;
	_scissorsItem->currAnimIndex = 0;
	_isAlreadyGet = false;
}

static void Update(GameObject* this, int64 deltaTime)
{
	//if (_isDroped)
	//{
	//	return;
	//}

	//if (_isNowDrop)
	//{
	//	this->posY += 1 * deltaTime;
	//	if (this->posY > 9000)
	//	{
	//		_isDroped = true;
	//	}
	//	return;
	//}

	////트리거 좌표 설정
	//Vector2 vec;
	//vec.x = 4575 - _player->posX;
	//vec.y = 8800 - _player->posY;

	//if (NormVector2(&vec) < 100.0f)
	//{
	//	this->posX = 4575;
	//	this->posY = 8800;
	//	_isNowDrop = true;
	//}
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (g_isOnMenu)
	{
		return;
	}

	switch (vkKey)
	{
		case 0x46: // f 키 입력일 경우.
		{
			//플레이어와 일정 거리 이하일 경우 상호작용 가능
			Vector2 vec;
			vec.x = this->posX - _player->posX;
			vec.y = this->posY - _player->posY;

			if (NormVector2(&vec) > 100.0f)
			{
				return;
			}

			if (_isAlreadyGet)
			{
				return;
			}

			this->currAnimIndex = 1;
		}
		break;
		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

GameObject* SetScissorsItem(GameObject* player, RACamera* camera)
{
	_player = player;
	_camera = camera;
	_scissorsItem = AllocGameObject();
	_scissorsItem->posX = ITEM_POS_X;
	_scissorsItem->posY = ITEM_POS_Y;
	_scissorsItem->layer = LAYER_COMMON_OBJECT;
	_scissorsItem->rotation = 0;
	_scissorsItem->scaleX = 0;
	_scissorsItem->scaleY = 0;
	_scissorsItem->Start = Start;
	_scissorsItem->Update = Update;

	_scissorsItem->animSize = 2;
	_scissorsItem->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _scissorsItem->animSize);

	SetAnimation(_scissorsItem->animArray, 0, 1000, 1);
	SetImage(_scissorsItem->animArray, 0, 0, STORY_0_ITEM_0);

	SetAnimation(_scissorsItem->animArray, 1, 1000, 1);
	SetImage(_scissorsItem->animArray, 1, 0, NO_VISUAL_IMAGE);

	SetInputCallback(_scissorsItem, OnKeyUp, OnKeyDown);

	return _scissorsItem;
}

void DisableScissorsItem()
{
	DisableGameObject(_scissorsItem);
}