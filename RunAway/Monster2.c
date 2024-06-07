#include "Monster2.h"

#include "RAGameEngine.h"
#include "RAGameObject.h"
#include "RAVector2.h"

#include "define.h"
#include "ReadMapData.h"
#include "WorldMap.h"
#include "OutOfBody.h"
#include "SceneGamePlay.h"

#include <math.h>
#include <time.h>
#include <windows.h>

static GameObject* _monster;
static GameObject* _player;
static Map* _map;

static float _moveSpeed = 0.15f;
static int _count;

static int32 expectX;
static int32 expectY;

static bool _isFrontState = true;
static bool _isSideState = true;
static bool _isTile = false;

extern bool _isLightOn;
extern bool g_isOnMenu;
extern bool g_isPlayerViewStory;
extern bool g_isCharecterMode;

static void Start(GameObject* this)
{
	const double PI = 3.1415926;
	int spawnRange = rand() % 411 + 640;	// 640 ~ 1050px
	int rotation = rand() % 360;
	double radian = PI / (180 * rotation);
	double posXCos = cos(PI / radian) * spawnRange;
	double posYSin = sin(PI / radian) * spawnRange;

	this->posX = _player->posX + (float)posXCos;
	this->posY = _player->posY + (float)posYSin;

	//// 벽에 겹쳐 소환이 안되게 하는 코드 (현재 사용안함)
	//while (_isTile == false)
	//{
	//	int spawnRange = rand() % 411 + 640;	// 640 ~ 1050px
	//	int rotation = rand() % 360;
	//	double radian = PI / (180 * rotation);
	//	double posXCos = cos(PI / radian) * spawnRange;
	//	double posYSin = sin(PI / radian) * spawnRange;

	//	this->posX = _player->posX + (float)posXCos;
	//	this->posY = _player->posY + (float)posYSin;

	//	expectX = (int32)this->posX / 150;
	//	expectY = (int32)this->posY / 150;

	//	if (_map->mapArray[expectY * _map->width + expectX + 1].argb == TILE &&
	//		_map->mapArray[expectY * _map->width + expectX].argb == TILE &&
	//		_map->mapArray[expectY * _map->width + expectX - 1].argb == TILE)
	//	{
	//		_isTile = true;
	//	}
	//}
}

static void Update(GameObject* this, int64 deltaTime)
{
	if (g_isOnMenu || g_isPlayerViewStory)
	{
		return;
	}

	Vector2 vector2;
	vector2.x = this->posX - _player->posX;
	vector2.y = this->posY - _player->posY;

	// 좌우 반전
	if (this->posX <= _player->posX)
	{
		this->isLeftDir = false;
	}
	else if (this->posX > _player->posX)
	{
		this->isLeftDir = true;
	}

	// 방향에 따른 애니메이션
	float tempX = _player->posX;
	float tempY = _player->posY;

	if (this->posX > (tempX -= 300) && this->posX < (tempX += 100) &&
		_isFrontState == true && this->posY <= _player->posY)
	{
		_isFrontState = false;
		ChangeAnimIndex(this, 0);	// front
	}
	else if (_isSideState == true && this->posY <= _player->posY)
	{
		_isSideState = false;
		ChangeAnimIndex(this, 1);	// front_side
	}
	else if (this->posX > (tempX -= 300) && this->posX < (tempX += 100) &&
		_isFrontState == false && this->posY > _player->posY)
	{
		_isFrontState = true;
		ChangeAnimIndex(this, 2);	// rear
	}
	else if (_isSideState == false && this->posY > _player->posY)
	{
		_isSideState = true;
		ChangeAnimIndex(this, 3); // rear_side
	}

	// 캐릭터가 충둘한 상태
	// 게임오버가 되어야 함
	if (NormVector2(&vector2) < 100)
	{
		GameOver();
	}

	// 방향만 가르키게 하기 위한 벡터 정규화
	NormalizationVector2(&vector2);

	// 메뉴가 없으면 player 추적
	if (g_isOnMenu != true)
	{
		this->posX -= vector2.x * _moveSpeed * deltaTime;
		this->posY -= vector2.y * _moveSpeed * deltaTime;
	}

	//// 벽을 통과 못하게 Player 추적 (현재 사용 안함)
	//float deltaMove = _moveSpeed * deltaTime;
	//if (this->posX <= _player->posX)
	//{
	//	int32 expectX = (int32)(this->posX + _moveSpeed) / 150 + 1;
	//	int32 expectY = (int32)this->posY / 150;
	//	if (_map->mapArray[expectY * _map->width + expectX].argb == TILE)
	//	{
	//		this->posX -= vector2.x * _moveSpeed * deltaTime;
	//	}
	//}
	//if (this->posX > _player->posX)
	//{
	//	int32 expectX = (int32)(this->posX - _moveSpeed) / 150 - 1;
	//	int32 expectY = (int32)this->posY / 150;
	//	if (_map->mapArray[expectY * _map->width + expectX].argb == TILE)
	//	{
	//		this->posX -= vector2.x * _moveSpeed * deltaTime;
	//	}
	//}
	//if (this->posY > _player->posY)
	//{
	//	int32 expectX = (int32)this->posX / 150;
	//	int32 expectY = (int32)(this->posY - _moveSpeed) / 150;
	//	if (_map->mapArray[expectY * _map->width + expectX + 1].argb == TILE &&
	//		_map->mapArray[expectY * _map->width + expectX].argb == TILE &&
	//		_map->mapArray[expectY * _map->width + expectX - 1].argb == TILE)
	//	{
	//		this->posY -= vector2.y * _moveSpeed * deltaTime;
	//	}
	//}
	//if (this->posY <= _player->posY)
	//{
	//	int32 expectX = (int32)this->posX / 150;
	//	int32 expectY = (int32)(this->posY + _moveSpeed) / 150;
	//	if (_map->mapArray[expectY * _map->width + expectX + 1].argb == TILE &&
	//		_map->mapArray[expectY * _map->width + expectX].argb == TILE &&
	//		_map->mapArray[expectY * _map->width + expectX - 1].argb == TILE)
	//	{
	//		this->posY -= vector2.y * _moveSpeed * deltaTime;
	//	}
	//}
}

void SetMonster2(GameObject* player, GameObject* monter, Map* map)
{
	_player = player;
	_map = map;

	monter->layer = LAYER_MONSTER;
	monter->posX = player->posX;
	monter->posY = player->posY;
	monter->rotation = 0.0f;
	monter->scaleX = 1.0f;
	monter->scaleY = 1.0f;
	monter->Start = Start;
	monter->Update = Update;

	monter->animSize = 4;
	monter->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * monter->animSize);
	monter->currAnimIndex = 0;

	bool frontAnim = SetAnimation(monter->animArray, 0, 300, 3);
	SetImage(monter->animArray, 0, 0, SHADOW_MONSTER_FRONT_0);
	SetImage(monter->animArray, 0, 1, SHADOW_MONSTER_FRONT_1);
	SetImage(monter->animArray, 0, 2, SHADOW_MONSTER_FRONT_2);

	bool frontSideAnim = SetAnimation(monter->animArray, 1, 300, 3);
	SetImage(monter->animArray, 1, 0, SHADOW_MONSTER_FRONT_SIDE_0);
	SetImage(monter->animArray, 1, 1, SHADOW_MONSTER_FRONT_SIDE_1);
	SetImage(monter->animArray, 1, 2, SHADOW_MONSTER_FRONT_SIDE_2);

	bool RearAnim = SetAnimation(monter->animArray, 2, 300, 3);
	SetImage(monter->animArray, 2, 0, SHADOW_MONSTER_REAR_0);
	SetImage(monter->animArray, 2, 1, SHADOW_MONSTER_REAR_1);
	SetImage(monter->animArray, 2, 2, SHADOW_MONSTER_REAR_2);

	bool RearSideAnim = SetAnimation(monter->animArray, 3, 300, 3);
	SetImage(monter->animArray, 3, 0, SHADOW_MONSTER_REAR_SIDE_0);
	SetImage(monter->animArray, 3, 1, SHADOW_MONSTER_REAR_SIDE_1);
	SetImage(monter->animArray, 3, 2, SHADOW_MONSTER_REAR_SIDE_2);
}