#include "Monster.h"

#include "RAGameEngine.h"
#include "RAGameObject.h"
#include "RAVector2.h"

#include "define.h"
#include "SceneGamePlay.h"

#include <stdlib.h>
#include <math.h> 
#include <time.h>

static GameObject* _monster;
static GameObject* _player;
static float _moveSpeed = 0.2f;
static bool _isFrontState = true;

extern bool _isLightOn;
extern bool g_isOnMenu;
extern bool g_isMonsterMgrEnable;
extern bool g_isPlayerViewStory;

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

	if (this->posX <= _player->posX)
	{
		this->isLeftDir = false;
	}
	else
	{
		this->isLeftDir = true;
	}

	if (_isFrontState == false && this->posY > _player->posY)
	{
		_isFrontState = true;
		ChangeAnimIndex(this, 1);
	}
	else if (_isFrontState == true && this->posY <= _player->posY)
	{
		_isFrontState = false;
		ChangeAnimIndex(this, 0);
	}

	// 캐릭터가 충둘한 상태
	// 게임오버가 되어야 함
	if (NormVector2(&vector2) < 100)
	{
		GameOver();
	}

	// 방향만 가르키게 하기 위한 벡터 정규화
	NormalizationVector2(&vector2);

	if (g_isOnMenu != true)
	{
		this->posX -= vector2.x * _moveSpeed * deltaTime;
		this->posY -= vector2.y * _moveSpeed * deltaTime;
	}
}

void SetMonster(GameObject* player, GameObject* monster)
{
	_player = player;

	monster->layer = LAYER_MONSTER; // 바닥: 0, 플레이어, 벽: 2
	monster->posX = player->posX;
	monster->posY = player->posY;
	monster->rotation = 0.0f;
	monster->scaleX = 1.0f;
	monster->scaleY = 1.0f;
	monster->Start = Start;
	monster->Update = Update;

	monster->animSize = 2;
	monster->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * monster->animSize);
	monster->currAnimIndex = 0;

	bool frontAnim = SetAnimation(monster->animArray, 0, 300, 4);
	SetImage(monster->animArray, 0, 0, GHOST_MONSTER_FRONT_0);
	SetImage(monster->animArray, 0, 1, GHOST_MONSTER_FRONT_1);
	SetImage(monster->animArray, 0, 2, GHOST_MONSTER_FRONT_2);
	SetImage(monster->animArray, 0, 3, GHOST_MONSTER_FRONT_3);

	bool rearAnim = SetAnimation(monster->animArray, 1, 300, 4);
	SetImage(monster->animArray, 1, 0, GHOST_MONSTER_REAR_0);
	SetImage(monster->animArray, 1, 1, GHOST_MONSTER_REAR_1);
	SetImage(monster->animArray, 1, 2, GHOST_MONSTER_REAR_2);
	SetImage(monster->animArray, 1, 3, GHOST_MONSTER_REAR_3);
}