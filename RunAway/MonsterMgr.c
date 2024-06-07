#include "MonsterMgr.h"

#include "RAGameEngine.h"
#include "define.h"
#include "SceneGamePlay.h"
#include "RAVector2.h"

#include <stdlib.h>
#include <math.h> 
#include <time.h>

static bool _isMonster = true;
static bool _isMonster2 = true;

static int _monsterCount;
static GameObject* MonsterPool[5];
static GameObject* MonsterPool2;
static GameObject* _player;
static GameObject* _monsterMgr;
static Map* _map;

static int64 _ghostCoolTime = 12000;
static int64 _shadowCoolTime = 3000;
static int64 _coolTime;

extern bool _isLightOn;
extern bool g_isOnMenu;
extern bool g_isCharecterMode;
extern bool g_isPlayerViewStory;

static void Start(GameObject* this)
{
	srand((unsigned int)time(NULL));
	_coolTime = 0;
	_monsterCount = 0;
	_isMonster2 = true;
}

static void DisableMonster1()
{
	for (int i = 0; i < _monsterCount; i++)
	{
		DisableGameObject(MonsterPool[_monsterCount]);
	}
}

static void Update(GameObject* this, int64 deltaTime)
{
	if (g_isOnMenu)
	{
		return;
	}

	if (g_isPlayerViewStory == true)
	{
		return;
	}

	if (g_isCharecterMode == false)
	{
		DisableGameObject(MonsterPool2);
		StopSound(EFFECT_SHADOW_SHOWUP);
		for (int i = 0; i < _monsterCount; i++)
		{
			DisableGameObject(MonsterPool[i]);
		}
		StopSound(EFFECT_GHOST_SHOWUP);
		//_isMonster2 = false;
		_coolTime = 0;
	}

	if (_isLightOn == true && _isMonster2 == true && g_isCharecterMode == true)
	{
		_coolTime += deltaTime;
		DisableGameObject(MonsterPool2);
		StopSound(EFFECT_SHADOW_SHOWUP);

		if (_coolTime > _ghostCoolTime)
		{
			EnableMonsterPool();
			_isMonster2 = false;
			_coolTime = 0;
		}
		_isMonster = true;
	}

	if (_isLightOn != true && _isMonster == true && g_isCharecterMode == true)
	{
		for (int i = 0; i < _monsterCount; i++)
		{
			DisableGameObject(MonsterPool[i]);
		}
		StopSound(EFFECT_GHOST_SHOWUP);
		if (g_isCharecterMode == true)
		{
			EnableMonsterPool2();
			_isMonster = false;
			_coolTime = 0;
		}
		_isMonster2 = true;
	}

}

GameObject* SetMonsterMgr(GameObject* player, Map* map)
{
	_player = player;
	_map = map;

	_monsterMgr = AllocGameObject();
	_monsterMgr->layer = LAYER_MONSTER; // 바닥: 0, 플레이어, 벽: 2
	_monsterMgr->posX = player->posX;
	_monsterMgr->posY = player->posY;
	_monsterMgr->rotation = 0.0f;
	_monsterMgr->scaleX = 1.0f;
	_monsterMgr->scaleY = 1.0f;
	_monsterMgr->Start = Start;
	_monsterMgr->Update = Update;

	_monsterMgr->animArray = NULL;
	_monsterMgr->animSize = 0;
	_monsterMgr->currAnimIndex = 0;

	MonsterPool[0] = AllocGameObject();
	MonsterPool[1] = AllocGameObject();
	MonsterPool[2] = AllocGameObject();
	MonsterPool[3] = AllocGameObject();
	MonsterPool[4] = AllocGameObject();

	SetMonster(player, MonsterPool[0]);
	SetMonster(player, MonsterPool[1]);
	SetMonster(player, MonsterPool[2]);
	SetMonster(player, MonsterPool[3]);
	SetMonster(player, MonsterPool[4]);

	MonsterPool2 = AllocGameObject();
	SetMonster2(player, MonsterPool2, _map);

	return _monsterMgr;
}

void EnableMonsterMgr()
{
	EnableGameObject(_monsterMgr);
}

void EnableMonsterPool()
{
	_monsterCount = rand() % 3 + 3;		// 몬스터 3~5 랜덤 생성
	for (int i = 0; i < _monsterCount; i++)
	{
		EnableGameObject(MonsterPool[i]);
	}
	PlayEffectSound(EFFECT_GHOST_SHOWUP);
}

void EnableMonsterPool2()
{
	EnableGameObject(MonsterPool2);
	PlayEffectSound(EFFECT_SHADOW_SHOWUP);
}

void DisableMonsterMgr()
{
	DisableGameObject(_monsterMgr);

	for (int i = 0; i < _monsterCount; i++)
	{
		DisableGameObject(MonsterPool[i]);
	}
	StopSound(EFFECT_GHOST_SHOWUP);
	DisableGameObject(MonsterPool2);
	StopSound(EFFECT_SHADOW_SHOWUP);
}