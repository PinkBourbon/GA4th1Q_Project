#include "Player.h"

#include "RAGameEngine.h"
#include "RAGameObject.h"
#include "RACamera.h"
#include "ReadMapData.h"
#include "WorldMap.h"
#include "RAInput.h"
#include "RAAnimation.h"
#include "MonsterMgr.h"
#include "Monster.h"
#include "SoundManager.h"
#include "OutOfBody.h"
#include "define.h"

typedef enum _eMoveDirectionFlag
{
	NONE = 0x0000,
	RIGHT = 0x0001,
	UP = 0x0002,
	LEFT = 0x0004,
	DOWN = 0x0008,
}eMoveDirectionFlag;

//typedef enum _ePlayerButtonDirectionFlag
//{
//	ButtonA = 0x0000,
//	ButtonS = 0x0001
//}ePlayerButtonDirectionFlag;

extern bool g_isOnMenu;
extern bool g_isPlayerViewStory;

static GameObject* _player;
static float _moveSpeed = 0.3f;
static eMoveDirectionFlag _moveDir;
bool g_isCharecterMode = true;
static int64 _modeChangeCooltime = 10000; // 30000ms
static int64 _elapsedCooltime = 0;

static GameObject* _outOfBody;
static GameObject* _lightMask;
bool _isLightOn = true;

static RACamera* _camera;

static Map* _map;
static int _mazeSizeX;
static int _mazeSizeY;

static bool _isPlayWalkSound;


static void Start(GameObject* this)
{
	//����Ʈ ����ũ Ȱ��ȭ
	_isLightOn = true;
	ChangeAnimIndex(_lightMask, 0);
	_lightMask->posX = _player->posX;
	_lightMask->posY = _player->posY;
	EnableGameObject(_lightMask);

	// ī�޶� �̵� ��� ��ǥ ����
	int cameraPosX = (int32)this->posX - _camera->screenPixelWidth / 2;
	int cameraPosY = (int32)this->posY - _camera->screenPixelHeight / 2;

	if (cameraPosX < 0)
	{
		cameraPosX = 0;
	}
	else if (cameraPosX > _mazeSizeX - _camera->screenPixelWidth)
	{
		cameraPosX = _mazeSizeX - _camera->screenPixelWidth;
	}

	if (cameraPosY < 0)
	{
		cameraPosY = 0;
	}
	else if (cameraPosY > _mazeSizeY - _camera->screenPixelHeight)
	{
		cameraPosY = _mazeSizeY - _camera->screenPixelHeight;
	}

	_camera->posX = cameraPosX;
	_camera->posY = cameraPosY;

	g_isCharecterMode = true;
	_moveDir = NONE;
	_elapsedCooltime = 30000;

	_player->posX = 4575;
	_player->posY = 9000;
	_player->isLeftDir = false;
	_player->currAnimIndex = 0;
}

static void ChangeOutOfBodyMode()
{
	g_isCharecterMode = false;
	_elapsedCooltime = 0;
	_moveDir = NONE;
	//ĳ���͸� ������ ���·� �ٲ��ְ�
	ChangeAnimIndex(_player, 0); 

	// ���� �����ִ� ���¸� ���� ���ش�.
	if (_isLightOn) 
	{
		_isLightOn = false;
		ChangeAnimIndex(_lightMask, 1);
	}

	if (_isPlayWalkSound == true)
	{
		StopSound(EFFECT_WALK);
		_isPlayWalkSound = false;
	}

	EnableGameObject(_outOfBody);
}

static void CharacterMove(GameObject* this, int64 deltaTime)
{
	float deltaMove = _moveSpeed * deltaTime;
	if (_moveDir & RIGHT)
	{
		int32 expectX = (int32)(this->posX + deltaMove) / 150 + 1;
		int32 expectY = (int32)this->posY / 150;

		// �̵��� ���� mapindex�� ĳ������ �߽��� + 1��ŭ (������ ���� ��ǥ)�� Ÿ���̸� �̵�����
		if (_map->mapArray[expectY * _map->width + expectX].argb == TILE) 
		{
			this->posX += deltaMove;
		}
	}
	if (_moveDir & LEFT)
	{
		int32 expectX = (int32)(this->posX - deltaMove) / 150 - 1;
		int32 expectY = (int32)this->posY / 150;

		// �̵��� ���� mapindex�� ĳ������ �߽��� - 1��ŭ (���� ���� ��ǥ)�� Ÿ���̸� �̵�����
		if (_map->mapArray[expectY * _map->width + expectX].argb == TILE) 
		{
			this->posX -= deltaMove;
		}
	}
	if (_moveDir & UP)
	{
		int32 expectX = (int32)this->posX / 150;
		int32 expectY = (int32)(this->posY - deltaMove) / 150;

		// �̵��� ���� mapindex�� ĳ������ ����, ������ �Ѵ� tile�̾�� �̵�����
		if (_map->mapArray[expectY * _map->width + expectX + 1].argb == TILE &&
			_map->mapArray[expectY * _map->width + expectX].argb == TILE &&
			_map->mapArray[expectY * _map->width + expectX - 1].argb == TILE) 
		{
			this->posY -= deltaMove;
		}
	}
	if (_moveDir & DOWN)
	{
		int32 expectX = (int32)this->posX / 150;
		int32 expectY = (int32)(this->posY + deltaMove) / 150;

		// �̵��� ���� mapindex�� ĳ������ ����, ������ �Ѵ� tile�̾�� �̵�����
		if (_map->mapArray[expectY * _map->width + expectX + 1].argb == TILE &&
			_map->mapArray[expectY * _map->width + expectX].argb == TILE &&
			_map->mapArray[expectY * _map->width + expectX - 1].argb == TILE) 
		{
			this->posY += deltaMove;
		}
	}
}

static void CameraMove(GameObject* this, int64 deltaTime)
{
	// ī�޶� �̵� ��� ��ǥ ����
	int cameraPosX = (int32)this->posX - _camera->screenPixelWidth / 2;
	int cameraPosY = (int32)this->posY - _camera->screenPixelHeight / 2;

	int lightMaskPosX = (int32)this->posX;
	int	lightMaskPosY = (int32)this->posY;

	int mazeSizeX = 9150;
	int mazeSizeY = 9150;

	if (cameraPosX < 0)
	{
		_camera->posX = 0;
	}
	else if (cameraPosX > mazeSizeX - _camera->screenPixelWidth)
	{
		_camera->posX = mazeSizeX - _camera->screenPixelWidth;
	}
	else
	{
		_camera->posX = cameraPosX;
	}

	if (cameraPosY < 0)
	{
		_camera->posY = 0;
	}
	else if (cameraPosY > _mazeSizeY - _camera->screenPixelHeight)
	{
		_camera->posY = _mazeSizeY - _camera->screenPixelHeight;
	}
	else
	{
		_camera->posY = cameraPosY;
	}

	if (lightMaskPosX > 0 && lightMaskPosX < mazeSizeX)
	{
		_lightMask->posX = (float)lightMaskPosX;
	}
	if (lightMaskPosY > 0 && lightMaskPosY < mazeSizeY)
	{
		_lightMask->posY = (float)lightMaskPosY;
	}

	//// �� ���
	//if (_buttonDir & ButtonA)
	//{
	//	// �ѱ� 
	//	_isLightOn = true;
	//	DisableMonster();
	//}
	//if (_buttonDir & ButtonS)
	//{
	//	// ����
	//	_isLightOn = false;
	//	SetMonsterMgr(0, 0, _isLightOn);
	//	SetMonster(this);
	//}
}

static void Update(GameObject* this, int64 deltaTime)
{
	if (g_isOnMenu) // �޴��� ������ ���
	{
		return;
	}

	if (g_isPlayerViewStory)
	{
		return;
	}

	if (g_isCharecterMode == false) // ��ü��Ż ����� ��� 
	{
		CameraMove(_outOfBody, deltaTime);
		return;
	}

	_elapsedCooltime += deltaTime;

	if (_isLightOn)
	{
		CharacterMove(this, deltaTime);
		CameraMove(this, deltaTime);
	}
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (g_isOnMenu) // �޴��� ������ ���
	{
		return;
	}

	if (g_isPlayerViewStory)
	{
		return;
	}

	if (g_isCharecterMode == false) // ��ü��Ż ����� ��� 
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

		case VK_SPACE:
		{
			
		}
		break;

		case 0x41: // a �� ���
		{
			_isLightOn = !_isLightOn;
			if (_isLightOn)
			{
				ChangeAnimIndex(_lightMask, 0);
			}
			else
			{
				ChangeAnimIndex(_lightMask, 1);
			}
		}
		break;

		case 0x53: // s �� ���
		{
			if (_elapsedCooltime >= _modeChangeCooltime)
			{
				ChangeOutOfBodyMode();
			}
		}
		break;

		default:
			break;
	}


	if (_moveDir != NONE)
	{
		if (_isPlayWalkSound == false)
		{
			// �����̴� ���� ��� ����
			PlayEffectSound(EFFECT_WALK);
			_isPlayWalkSound = true;
		}
		if ((_moveDir & UP) != 0)
		{
			if (this->currAnimIndex != 2)
			{
				ChangeAnimIndex(this, 2);
			}
		}
		else
		{
			if (this->currAnimIndex != 1)
			{
				ChangeAnimIndex(this, 1);
			}
		}
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{
	if (g_isCharecterMode == false) // ��ü��Ż ����� ��� 
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

	if (_moveDir == NONE)
	{
		if (_isPlayWalkSound == true)
		{
			// �����̴� ���� ����
			StopSound(EFFECT_WALK);
			_isPlayWalkSound = false;
		}
		ChangeAnimIndex(this, 0);
	}
}

GameObject* SetPlayer(RACamera* camera, Map* map, GameObject* outOutOfBody)
{
	_map = map;

	_mazeSizeX = map->width * 150;
	_mazeSizeY = map->height * 150 + 40;

	_camera = camera;

	_player = AllocGameObject();
	_player->layer = LAYER_COMMON_OBJECT;
	_player->posX = 4575;
	_player->posY = 9000;
	_player->rotation = 0.0f;
	_player->scaleX = 1.0f;
	_player->scaleY = 1.0f;

	_player->Start = Start;
	_player->Update = Update;

	SetInputCallback(_player, OnKeyUp, OnKeyDown);

	_player->animSize = 3;
	_player->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _player->animSize);

	bool IdieAnim = SetAnimation(_player->animArray, 0, 300, 1);
	SetImage(_player->animArray, 0, 0, PLAYER_IDLE_0);

	bool MoveLeftRightAnim = SetAnimation(_player->animArray, 1, 200, 4);
	SetImage(_player->animArray, 1, 0, PLAYER_FRONT_0);
	SetImage(_player->animArray, 1, 1, PLAYER_FRONT_1);
	SetImage(_player->animArray, 1, 2, PLAYER_FRONT_2);
	SetImage(_player->animArray, 1, 3, PLAYER_FRONT_3);

	bool MoveUpDownAnim = SetAnimation(_player->animArray, 2, 200, 4);
	SetImage(_player->animArray, 2, 0, PLAYER_REAR_0);
	SetImage(_player->animArray, 2, 1, PLAYER_REAR_1);
	SetImage(_player->animArray, 2, 2, PLAYER_REAR_2);
	SetImage(_player->animArray, 2, 3, PLAYER_REAR_3);
	
	//��ü��Ż ����
	_outOfBody = SetOutOfBody(_player, _map);

	// ����Ʈ ����Ʈ ����
	_lightMask = AllocGameObject();

	_lightMask->layer = 3;
	_lightMask->posX = _player->posX;
	_lightMask->posY = _player->posY;
	_lightMask->isLeftDir = true;

	_lightMask->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * 2);
	_lightMask->animSize = 2;
	_lightMask->currAnimIndex = 0;

	SetAnimation(_lightMask->animArray, 0, 1000, 1);
	SetImage(_lightMask->animArray, 0, 0, SCREENLIGHT_B);

	SetAnimation(_lightMask->animArray, 1, 1000, 1);
	SetImage(_lightMask->animArray, 1, 0, SCREENLIGHT_S);

	_lightMask->Start = nullptr;
	_lightMask->Update = nullptr;

	outOutOfBody = _outOfBody;
	return _player;
}

void DisablePlayer()
{
	DisableGameObject(_lightMask);
	if (g_isCharecterMode == false)
	{
		DisableGameObject(_outOfBody);
	}

	if (_isPlayWalkSound == true)
	{
		// �����̴� ���� ����
		StopSound(EFFECT_WALK);
		_isPlayWalkSound = false;
	}
	DisableGameObject(_player);
}