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

static bool _isAlreadyRead;
static bool _isNowDrop;
static bool _isDroped;

static RACamera* _camera;
static GameObject* _player;
static GameObject* _storyItem;
static GameObject* _storyWallPaper;

static float prevPosX;
static float prevPosY;

static Start(GameObject* this)
{
	_storyItem->posX = ITEM_POS_X;
	_storyItem->posY = ITEM_POS_Y;
	_storyItem->isLeftDir = true;
	_storyItem->currAnimIndex = 0;
	_isAlreadyRead = false;
	_isNowDrop = false;
	_isDroped = false;
}

static void Update(GameObject* this, int64 deltaTime)
{
	if (_isDroped)
	{
		return;
	}

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

			if (NormVector2(&vec) > 150.0f)
			{
				return;
			}

			if (_isAlreadyRead)
			{
				return;
			}

			if (g_isPlayerViewStory)
			{
				g_isPlayerViewStory = false;
				_isAlreadyRead = true;
				DisableGameObject(_storyWallPaper);
				return;
			}

			g_isPlayerViewStory = true;
			this->currAnimIndex = 1;

			_storyWallPaper->posX = (float)_camera->posX;
			_storyWallPaper->posY = (float)_camera->posY;
			EnableGameObject(_storyWallPaper);
		}
		break;
		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

GameObject* SetStoryItem0(GameObject* player, RACamera* camera)
{
	_player = player;
	_camera = camera;
	_storyItem = AllocGameObject();
	_storyItem->posX = ITEM_POS_X;
	_storyItem->posY = ITEM_POS_Y;
	_storyItem->layer = LAYER_COMMON_OBJECT;
	_storyItem->rotation = 0;
	_storyItem->scaleX = 0;
	_storyItem->scaleY = 0;
	_storyItem->isLeftDir = true;
	_storyItem->Start = Start;
	_storyItem->Update = Update;

	_storyItem->animSize = 2;
	_storyItem->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _storyItem->animSize);

	SetAnimation(_storyItem->animArray, 0, 1000, 1);
	SetImage(_storyItem->animArray, 0, 0, STORY_0_ITEM_0);

	SetAnimation(_storyItem->animArray, 1, 1000, 1);
	SetImage(_storyItem->animArray, 1, 0, STORY_0_ITEM_1);

	SetInputCallback(_storyItem, OnKeyUp, OnKeyDown);

	_storyWallPaper = AllocGameObject();

	_storyWallPaper->layer = LAYER_UI;
	_storyWallPaper->rotation = 0;
	_storyWallPaper->scaleX = 0;
	_storyWallPaper->scaleY = 0;
	_storyWallPaper->isLeftDir = true;
	_storyWallPaper->Start = NULL;
	_storyWallPaper->Update = NULL;

	_storyWallPaper->animSize = 1;
	_storyWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _storyWallPaper->animSize);
	_storyWallPaper->currAnimIndex = 0;

	SetAnimation(_storyWallPaper->animArray, 0, 1000, 1);
	SetImage(_storyWallPaper->animArray, 0, 0, STORY_WALL_PAPER_0);

	return _storyItem;
}

void DisableStoryItem0()
{
	if (g_isPlayerViewStory == true)
	{
		g_isPlayerViewStory = false;
		DisableGameObject(_storyWallPaper);
	}
	DisableGameObject(_storyItem);
}