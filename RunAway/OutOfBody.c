#include "OutOfBody.h"
#include "RAGameEngine.h"
#include "RAInput.h"
#include "RAVector2.h"
#include "ReadMapData.h"
#include "WorldMap.h"
#include "RAType.h"
#include "define.h"

typedef enum _eMoveDirectionFlag
{
	NONE = 0x0000,
	RIGHT = 0x0001,
	UP = 0x0002,
	LEFT = 0x0004,
	DOWN = 0x0008,
}eMoveDirectionFlag;

GameObject* _player;
extern bool g_isCharecterMode;
Map* _map;

static int64 _modeChangeCooltime = 10000;
static int64 _elapsedCooltime = 0;
static bool _isReturnMode = false;

static GameObject* _outOfBody;
static eMoveDirectionFlag _moveDir;
static float _outOfBodySpeed = 1.0f;

static void ChangeCharecterMode()
{
	_elapsedCooltime = 0;
	g_isCharecterMode = true;
	DisableGameObject(_outOfBody);
}

static void OutOfBodyMove(GameObject* this, int64 deltaTime)
{
	//유령벽일때 추가로 이동 가능 로직 추가.
	float deltaMove = _outOfBodySpeed * deltaTime;
	if (_moveDir & RIGHT)
	{
		int32 expectX = (int32)(this->posX + deltaMove + 75) / 150;
		int32 expectY = (int32)this->posY / 150;
		if (_map->mapArray[expectY * _map->width + expectX].argb == TILE ||
			_map->mapArray[expectY * _map->width + expectX].argb == PASSWALL) // 이동할 곳의 mapindex가 캐릭터의 중심점 + 1만큼 (오른쪽 끝의 좌표)가 타일이면 이동가능
		{
			this->posX += deltaMove;
		}
	}
	if (_moveDir & LEFT)
	{
		int32 expectX = (int32)(this->posX - deltaMove - 75) / 150;
		int32 expectY = (int32)this->posY / 150;
		if (_map->mapArray[expectY * _map->width + expectX].argb == TILE || 
			_map->mapArray[expectY * _map->width + expectX].argb == PASSWALL) // 이동할 곳의 mapindex가 캐릭터의 중심점 - 1만큼 (왼쪽 끝의 좌표)가 타일이면 이동가능
		{
			this->posX -= deltaMove;
		}
	}
	if (_moveDir & UP)
	{
		int32 expectX = (int32)this->posX / 150;
		int32 expectY = (int32)(this->posY - deltaMove) / 150;
		if (_map->mapArray[expectY * _map->width + expectX].argb == TILE || 
			_map->mapArray[expectY * _map->width + expectX].argb == PASSWALL) // 이동할 곳의 mapindex가 캐릭터의 왼쪽, 오른쪽 둘다 tile이어야 이동가능
		{
			this->posY -= deltaMove;
		}
	}
	if (_moveDir & DOWN)
	{
		int32 expectX = (int32)this->posX / 150;
		int32 expectY = (int32)(this->posY + deltaMove) / 150;
		if (_map->mapArray[expectY * _map->width + expectX].argb == TILE || 
			_map->mapArray[expectY * _map->width + expectX].argb == PASSWALL) // 이동할 곳의 mapindex가 캐릭터의 왼쪽, 오른쪽 둘다 tile이어야 이동가능
		{
			this->posY += deltaMove;
		}
	}
}

void Start(GameObject* this)
{
	_moveDir = NONE;
	this->posX = _player->posX;
	this->posY = _player->posY;
	_elapsedCooltime = 0;
	_isReturnMode = false;
}

void Update(GameObject* this, int64 deltaTime)
{
	if (_isReturnMode)
	{
		Vector2 vec;
		vec.x = this->posX - _player->posX;
		vec.y = this->posY - _player->posY;

		if (NormVector2(&vec) < 100)
		{
			ChangeCharecterMode();
		}

		NormalizationVector2(&vec);

		this->posX -= vec.x * _outOfBodySpeed * deltaTime;
		this->posY -= vec.y * _outOfBodySpeed * deltaTime;
		return;
	}

	if (_elapsedCooltime < _modeChangeCooltime)
	{
		_elapsedCooltime += deltaTime;
	}
	else//쿨타임이 다 됐을 경우 강제로 캐릭터 상태로 변경
	{
		_isReturnMode = true;
		return;
	}

	OutOfBodyMove(this, deltaTime);
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (_isReturnMode)
	{
		return;
	}

	switch (vkKey)
	{
		case VK_RIGHT:
		{
			_moveDir ^= RIGHT;
			_moveDir &= ~LEFT;

			this->isLeftDir = false;
		}
		break;

		case VK_UP:
		{
			_moveDir ^= UP;
			_moveDir &= ~DOWN;

		}
		break;

		case VK_LEFT:
		{
			_moveDir ^= LEFT;
			_moveDir &= ~RIGHT;

			this->isLeftDir = true;
		}
		break;

		case VK_DOWN:
		{
			_moveDir ^= DOWN;
			_moveDir &= ~UP;
		}
		break;

		case 0x53://s 일 경우
		{
			if (_elapsedCooltime > 100)
			{
				_isReturnMode = true;
			}
		}
		break;
		default:
			break;
	}

	if ((_moveDir & UP) != 0)
	{
		ChangeAnimIndex(this, 1);
	}
	else
	{
		ChangeAnimIndex(this, 0);
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{
	if (_isReturnMode)
	{
		return;
	}

	switch (vkKey)
	{
		case VK_RIGHT:
		{
			_moveDir &= ~RIGHT;
		}
		break;

		case VK_UP:
		{
			_moveDir &= ~UP;
		}
		break;

		case VK_LEFT:
		{
			_moveDir &= ~LEFT;
		}
		break;

		case VK_DOWN:
		{
			_moveDir &= ~DOWN;
		}
		break;

		default:
			break;
	}
}

GameObject* SetOutOfBody(GameObject* player, Map* map)
{
	_player = player;
	_map = map;

	_outOfBody = AllocGameObject();
	_outOfBody->layer = LAYER_MONSTER;
	_outOfBody->posX = 0;
	_outOfBody->posY = 0;
	_outOfBody->rotation = 0.0f;
	_outOfBody->scaleX = 1.0f;
	_outOfBody->scaleY = 1.0f;
	_outOfBody->isLeftDir = false;
	_outOfBody->Start = Start;
	_outOfBody->Update = Update;

	SetInputCallback(_outOfBody, OnKeyUp, OnKeyDown);

	_outOfBody->animSize = 2;
	_outOfBody->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _outOfBody->animSize);
	_outOfBody->currAnimIndex = 0;

	SetAnimation(_outOfBody->animArray, 0, 300, 2);
	SetImage(_outOfBody->animArray, 0, 0, PLAYER_SOUL_FRONT_0);
	SetImage(_outOfBody->animArray, 0, 1, PLAYER_SOUL_FRONT_1);

	SetAnimation(_outOfBody->animArray, 1, 300, 2);
	SetImage(_outOfBody->animArray, 1, 0, PLAYER_SOUL_REAR_0);
	SetImage(_outOfBody->animArray, 1, 1, PLAYER_SOUL_REAR_1);


	return _outOfBody;
}