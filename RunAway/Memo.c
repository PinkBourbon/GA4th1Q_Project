#include "Memo.h"

#include "RAGameEngine.h"
#include "RAInput.h"
#include "RAAnimation.h"
#include "RACamera.h"
#include "RAVector2.h"
#include "RAType.h"
#include "define.h"

extern bool g_isOnMenu;
extern bool g_isPlayerViewStory;

static bool _isAlreadyRead;
static bool _isNowDrop;
static bool _isDroped;

static RACamera* _camera;
static GameObject* _player;
static GameObject* _memo;
static GameObject* _memoWallPaper;

static float prevPosX;
static float prevPosY;

static Start(GameObject* this)
{
	_memo->posX = 0;//_player->posX;
	_memo->posY = 0;// _player->posY;
	_memo->isLeftDir = true;
	_memo->currAnimIndex = 0;
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

	if (_isNowDrop)
	{
		this->posY += 1 * deltaTime;
		if (this->posY > 9000)
		{
			_isDroped = true;
		}
		return;
	}

	Vector2 vec;
	vec.x = 4575 - _player->posX;
	vec.y = 8800 - _player->posY;

	if (NormVector2(&vec) < 100.0f)
	{
		this->posX = 4575;
		this->posY = 8800;
		_isNowDrop = true;
	}
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (g_isOnMenu)
	{
		return;
	}

	switch (vkKey)
	{
		case 0x46: // f Ű
		{

			Vector2 vec;
			vec.x = this->posX - _player->posX;
			vec.y = this->posY - _player->posY;

			if (NormVector2(&vec) > 100.0f)
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
				DisableGameObject(_memoWallPaper);
				return;
			}

			g_isPlayerViewStory = true;
			this->currAnimIndex = 1;

			_memoWallPaper->posX = (float)_camera->posX;
			_memoWallPaper->posY = (float)_camera->posY;
			EnableGameObject(_memoWallPaper);
		}
		break;
		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

GameObject* SetMemo(GameObject* player, RACamera* camera)
{
	_player = player;
	_camera = camera;
	_memo = AllocGameObject();
	_memo->layer = LAYER_COMMON_OBJECT;
	_memo->rotation = 0;
	_memo->scaleX = 0;
	_memo->scaleY = 0;
	_memo->Start = Start;
	_memo->Update = Update;

	_memo->animSize = 2;
	_memo->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _memo->animSize);

	SetAnimation(_memo->animArray, 0, 1000, 1);
	SetImage(_memo->animArray, 0, 0, MEMO_ITEM_0);

	SetAnimation(_memo->animArray, 1, 1000, 1);
	SetImage(_memo->animArray, 1, 0, MEMO_ITEM_1);

	SetInputCallback(_memo, OnKeyUp, OnKeyDown);

	_memoWallPaper = AllocGameObject();

	_memoWallPaper->layer = LAYER_UI;
	_memoWallPaper->rotation = 0;
	_memoWallPaper->scaleX = 0;
	_memoWallPaper->scaleY = 0;
	_memoWallPaper->Start = NULL;
	_memoWallPaper->Update = NULL;

	_memoWallPaper->animSize = 1;
	_memoWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _memoWallPaper->animSize);
	_memoWallPaper->currAnimIndex = 0;

	SetAnimation(_memoWallPaper->animArray, 0, 1000, 1);
	SetImage(_memoWallPaper->animArray, 0, 0, MEMO_WALL_PAPER);

	return _memo;
}

void DisableMemo()
{
	if (g_isPlayerViewStory == true)
	{
		g_isPlayerViewStory = false;
		DisableGameObject(_memoWallPaper);
	}
	DisableGameObject(_memo);
}